
public class MakeCoffee {
	Coffee order;
	
	MakeCoffee() {
		order = new BasicCoffee();
	}
	
	public void withCream() {
		order = new Cream(order);
	}
	public void withExtraShot() {
		order = new ExtraShot(order);
	}
	public void withSugar() {
		order = new Sugar(order);
	}
	public void withSprinkles() {
		order = new Sprinkles(order);
	}
	public void withPumpkinSpice() {
		order = new PumpkinSpice(order);
	}
	
	public double getOrder() {
		return order.makeCoffee();
	}
}
