"""
This file contains the functions to fetch, save and load the data.
"""
# Import libraries
import json
import requests
import sys

# Define the function to fetch the data
def fetch_data(url, params, headers):
    response = requests.get(url, params=params, headers=headers)
    data = json.loads(response.text)

    # Check if the request was successful
    if data['status'] == 'OK':
        print('Request successful')

    # Check if the request was not successful
    elif data['status'] == 'ZERO_RESULTS':
        print('No results found')
        sys.exit()
        
    return data

def fetch_routes(data):
    routes = data['routes']
    return routes

# Define the function to save the data
def save_data(data, filename):
    with open(filename, 'w') as outfile:
        json.dump(data, outfile)
    
# Define the function to load the data
def load_data(filename):
    with open(filename) as json_file:
        data = json.load(json_file)
    return data
