"""
This script will convert the json file and insert the data to a mysql database
"""

# Import libraries
import mysql.connector
from utils import fetch_data

# Define the API key
apikey = 'AIzaSyBFzQRR1MO5OR-jXNgV7RqRpqSnEpUy-XI'

# Define the URL
url = 'https://maps.googleapis.com/maps/api/directions/json'

origin = 'Rua dos Peões, Braga, Portugal'
destination = 'Rua da Universidade, Braga, Portugal'

# Define the parameters
params = {
    'origin': origin,
    'destination': destination,
    'mode': 'driving',
    'key': 'AIzaSyBFzQRR1MO5OR-jXNgV7RqRpqSnEpUy-XI'
}

# Define the headers
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36'
}

# Fetch the data
data = fetch_data(url, params, headers)

# Conector ao MySQL
# mysql_conn = mysql.connector.connect(
#     host='localhost',
#     user='root',
#     password='',
#     database='traffic_db',
#     port = 3306,
# )

# Conector ao MySQL da Cloud
mysql_conn = mysql.connector.connect(
    host='34.135.225.222',
    user='purp',
    password='purp',
    database='traffic_db',
    port = 3306,
)

# Create cursor object
cursor = mysql_conn.cursor()

waypoint_routes = {}
# Insert into 'geocoded_waypoints' table
for waypoint in data['geocoded_waypoints']:
        query = """INSERT INTO geocoded_waypoints (geocoder_status, place_id) VALUES (%s, %s)"""
        values = (waypoint['geocoder_status'], waypoint['place_id'])
        cursor.execute(query, values)

# Create dict with all the ids:
cursor.execute("SELECT id_geocoded_waypoints FROM geocoded_waypoints")
waypoint_ids = cursor.fetchall()
for id in waypoint_ids:
    waypoint_routes[id[0]] = None

# Insert into 'routes' table
# there might be many routes
# Insert the data into the table
for route in data['routes']:
    bounds = route.get('bounds', {})
    bounds_ne_lat = bounds.get('northeast', {}).get('lat', 0.0)
    bounds_ne_lon = bounds.get('northeast', {}).get('lng', 0.0)
    bounds_sw_lat = bounds.get('southwest', {}).get('lat', 0.0)
    bounds_sw_lon = bounds.get('southwest', {}).get('lng', 0.0)
    bounds_nw_lat = bounds.get('northwest', {}).get('lat', 0.0)
    bounds_nw_lon = bounds.get('northwest', {}).get('lng', 0.0)
    bounds_se_lat = bounds.get('southeast', {}).get('lat', 0.0)
    bounds_se_lon = bounds.get('southeast', {}).get('lng', 0.0)

    query = """INSERT INTO routes (bounds_ne_lat, bounds_ne_lon, bounds_sw_lat, bounds_sw_lon, bounds_nw_lat, bounds_nw_lon, bounds_se_lat, bounds_se_lon) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"""
    values = ( bounds_ne_lat, bounds_ne_lon, bounds_sw_lat, bounds_sw_lon, bounds_nw_lat, bounds_nw_lon, bounds_se_lat, bounds_se_lon )
    cursor.execute(query, values)

    # Keep the last id of route
    id_routes = cursor.lastrowid

    # Connect the waypoint to the route
    for waypoint_id, route_id in waypoint_routes.items():
        waypoint_routes[waypoint_id] = id_routes

    # Insert into 'routes_has_geocoded_waypoints'
    # te table has 2 foreign keys: id_routes and id_geocoded_waypoints
    # Insert into 'routes_has_geocoded_waypoints'
    for waypoint_id, route_id in waypoint_routes.items():
        query = """INSERT INTO routes_has_geocoded_waypoints (id_routes, id_geocoded_waypoints) VALUES (%s, %s)"""
        values = (route_id, waypoint_id)
        cursor.execute(query, values)

    # Insert legs for the current route
    for leg in route['legs']:
        # We won't have via_waypoints for now
        # Insert the via_waypoints (if they exist)
        # for waypoint in leg['via_waypoint']:
        #     waypoint_order_value = 1
        #     if waypoint is None:
        #     # Insert all fields as null
        #         query = """INSERT INTO via_waypoints (location_lat, location_lon, waypoint_order_value) VALUES (%s, %s, %s)"""
        #         values = (None, None, None)
        #         cursor.execute(query, values)
        #     else:
        #         query = """INSERT INTO via_waypoints (location_lat, location_lon, waypoint_order_value) VALUES (%f, %f, %f)"""
        #         values = (waypoint['lat'], waypoint['lng'], waypoint_order_value)
        #         # convert to float
        #         values = [float(v) for v in values]
        #         cursor.execute(query, values)
        #         # Get the ID of the inserted waypoint
        #         waypoint_order_value += 1
        #     id_via_waypoint = cursor.lastrowid

        # Extract relevant data from leg dictionary
        distance_text = leg['distance']['text']
        distance_value = leg['distance']['value']
        duration_text = leg['duration']['text']
        duration_value = leg['duration']['value']
        start_address = leg['start_address']
        end_address = leg['end_address']
        start_location_lat = leg['start_location']['lat']
        start_location_lon = leg['start_location']['lng']
        end_location_lat = leg['end_location']['lat']
        end_location_lon = leg['end_location']['lng']

        # Insert the data into the table
        query = """INSERT INTO legs (id_routes, distance_text, distance_value, duration_text, duration_value, start_address, end_address, start_location_lat, start_location_lon, end_location_lat, end_location_lon) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"""
        values = (id_routes, distance_text, distance_value, duration_text, duration_value, start_address, end_address, start_location_lat, start_location_lon, end_location_lat, end_location_lon )
        cursor.execute(query, values)

        # keep the last leg id
        id_legs = cursor.lastrowid

        # Insert each step as a new row in the steps table
        for step in leg['steps']:
            distance_text = step['distance']['text']
            distance_value = step['distance']['value']
            duration_text = step['duration']['text']
            duration_value = step['duration']['value']
            end_location_lat = step['end_location']['lat']
            end_location_lon = step['end_location']['lng']
            html_instructions = step['html_instructions']
            polyline_points = step['polyline']['points']
            start_location_lat = step['start_location']['lat']
            start_location_lon = step['start_location']['lng']
            travel_mode = step['travel_mode']

            # Check if the step has a maneuver
            if 'maneuver' not in step:
                # put null in the maneuver field
                maneuver = "NULL"
            else:
                # put the maneuver in the maneuver field
                maneuver = step['maneuver']
            
            query = """INSERT INTO steps (id_legs, distance_text, distance_value, duration_text, duration_value, end_location_lat, end_location_lon, html_instructions, maneuver, polyline_points, start_location_lat, start_location_lon, travel_mode) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"""
            values = (id_legs, distance_text, distance_value, duration_text, duration_value, end_location_lat, end_location_lon, html_instructions, maneuver, polyline_points, start_location_lat, start_location_lon, travel_mode )
            cursor.execute(query, values)

            # We won't have speed for now
            # speed entry to complete
            # Insert the speed_entry info
            # if leg['traffic_speed_entry']:
            #     for speed_entries in leg['traffic_speed_entry']:
            #      speed_value = speed_entries['value']
            # else:
            #     id_speed_entry = None

mysql_conn.commit()
# Close the connections
cursor.close()
mysql_conn.close()

print("Insertion Successful.")
