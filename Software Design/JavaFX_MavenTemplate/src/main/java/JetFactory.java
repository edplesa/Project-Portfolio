
public class JetFactory extends AbstractFactory{
	@Override 
	public Vehicle getVehicle(String vehicleType) {
		if (vehicleType.equalsIgnoreCase("F35")) {
			return new JetF35();
		} else if (vehicleType.equalsIgnoreCase("SU50")) {
			return new JetSU50();
		}
		return null;
	}
}

