
public class Sprinkles extends CoffeeDecorator{

	private double cost = .25;
	
	Sprinkles(Coffee specialCoffee){
		super(specialCoffee);
	}
	
	public double makeCoffee() {
		return specialCoffee.makeCoffee() + addSprinkles();
	}
	
	private double addSprinkles() {
		
		System.out.println(" + sprinkles: $.25");
		
		return cost;
	}
}
