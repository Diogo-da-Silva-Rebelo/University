import Controller.API.ControllerAPI;

public class API {
    public static void main(String[] args) {
        System.out.println("API a correr");
        ControllerAPI controllerAPI = new ControllerAPI();
        controllerAPI.run();
    }
}