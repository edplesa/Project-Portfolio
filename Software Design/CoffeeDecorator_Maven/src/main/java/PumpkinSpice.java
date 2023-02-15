
public class PumpkinSpice extends CoffeeDecorator{

	private double cost = .35;
	
	PumpkinSpice(Coffee specialCoffee){
		super(specialCoffee);
	}
	
	public double makeCoffee() {
		return specialCoffee.makeCoffee() + addPumpkinSpice();
	}
	
	private double addPumpkinSpice() {
		
		System.out.println(" + pumpkin spice: $.35");
		
		return cost;
	}
}
