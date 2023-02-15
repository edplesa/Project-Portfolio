
public class VehicleProducer {
	
	public static AbstractFactory getFactory(String vehicle) {
		
		if (vehicle.equalsIgnoreCase("JET")) {
			return new JetFactory();
		} else if (vehicle.equalsIgnoreCase("BOAT")) {
			return new BoatFactory();
		} else if (vehicle.equalsIgnoreCase("TANK")) {
			return new TankFactory();
		}else {
			return null;
		}		
	}
}
