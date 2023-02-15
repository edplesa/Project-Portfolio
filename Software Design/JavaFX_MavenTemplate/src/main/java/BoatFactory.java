
public class BoatFactory extends AbstractFactory{
	@Override 
	public Vehicle getVehicle(String vehicleType) {
		if (vehicleType.equalsIgnoreCase("DV15")) {
			return new BoatDV15();
		} else if (vehicleType.equalsIgnoreCase("RCB")) {
			return new BoatRCB();
		}
		return null;
	}
}

