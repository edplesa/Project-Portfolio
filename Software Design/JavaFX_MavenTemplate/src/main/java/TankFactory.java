
public class TankFactory extends AbstractFactory{
	@Override 
	public Vehicle getVehicle(String vehicleType) {
		if (vehicleType.equalsIgnoreCase("Abrams")) {
			return new TankAbrams();
		} else if (vehicleType.equalsIgnoreCase("T90")) {
			return new TankT90();
		}
		return null;
	}
}

