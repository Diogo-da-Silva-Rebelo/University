package CasaInteligente;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CasaInteligente {
    private String address;
    private List<SmartDevice> smartDevicesL;
    private Map<String, List<String>> idDevicesMap;

    //constructors
    public CasaInteligente() {
        setAddress("");
        smartDevicesL = new ArrayList<>();
        idDevicesMap = new HashMap<>();
    }

    public CasaInteligente(String address) {
        setAddress(address);
        smartDevicesL = new ArrayList<>();
        idDevicesMap = new HashMap<>();
    }

    public boolean existsDevice(String address) {
        return this.smartDevicesL.stream().anyMatch(d -> d.getId().equals(address));
    }

    public SmartDevice getDevice(String address) {
        return this.smartDevicesL.stream().filter(d -> d.getId().equals(address)).findAny().orElse(null);
    }

    public void setAllON(boolean sd) {
        this.smartDevicesL.forEach(e -> e.setON(sd));
    }

    public void addRoom(String division) {
        this.idDevicesMap.put(division, new ArrayList<>());
    }

    public boolean hasRoom(String division) {
        return this.idDevicesMap.containsKey(division);
    }

    public void addToRoom(String division, String object) {
        this.idDevicesMap.get(division).add(String.valueOf(getDevice(object)));
    }

    public boolean roomHasDevice(String division, String object) {
        return (this.idDevicesMap.get(division).stream().anyMatch(e -> e.equals(getDevice(object))));

    }

    //getters & setters
    public String getAddress() {
        return this.address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}