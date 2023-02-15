import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {

	@Test
	void testMakeCoffeeConstructor() {
		MakeCoffee c1 = new MakeCoffee();
		Coffee order = new BasicCoffee();
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for constructor");
	}
	
	@Test
	void testMakeCoffeeWithCream() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withCream();
		Coffee order = new Cream(new BasicCoffee());
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Cream");
	}
	
	@Test
	void testMakeCoffeeWithSugar() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withSugar();
		Coffee order = new Sugar(new BasicCoffee());
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Sugar");
	}
	
	@Test
	void testMakeCoffeeWithExtraShot() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withExtraShot();
		Coffee order = new ExtraShot(new BasicCoffee());
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Extra Shot");
	}

	@Test
	void testMakeCoffeeWithSprinkles() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withSprinkles();
		Coffee order = new Sprinkles(new BasicCoffee());
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Sprinkles");
	}
	
	@Test
	void testMakeCoffeeWithPumpkinSpice() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withPumpkinSpice();
		Coffee order = new PumpkinSpice(new BasicCoffee());
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Pumpkin Spice");
	}
	
	@Test
	void testMakeCoffeeWithPumpkinSpiceWithOther() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withPumpkinSpice();
		c1.withCream();
		Coffee order = new Cream(new PumpkinSpice(new BasicCoffee()));
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Pumpkin Spice and other topping");
	}
	
	@Test
	void testMakeCoffeeWithSprinklesWithOther() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withSprinkles();
		c1.withPumpkinSpice();
		Coffee order = new PumpkinSpice(new Sprinkles(new BasicCoffee()));
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Sprinkles and other topping");
	}
	
	@Test
	void testMakeCoffeeWithExtraShotWithOther() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withExtraShot();
		c1.withSprinkles();
		Coffee order = new Sprinkles(new ExtraShot(new BasicCoffee()));
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Extra Shot and other");
	}
	
	@Test
	void testMakeCoffeeWithSugarWithOther() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withSugar();
		c1.withExtraShot();
		Coffee order = new ExtraShot(new Sugar(new BasicCoffee()));
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Sugar and other");
	}
	
	@Test
	void testMakeCoffeeWithCreamWithOther() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withCream();
		c1.withSugar();
		Coffee order = new Sugar(new Cream(new BasicCoffee()));
		assertEquals(c1.getOrder(), order.makeCoffee(), "Value for MakeCoffee and Coffee are incorrect for Cream and other");
	}
	
	@Test
	void testMakeCoffeeDifferentPrices() {
		MakeCoffee c1 = new MakeCoffee();
		c1.withCream();
		MakeCoffee c2 = new MakeCoffee();
		c2.withPumpkinSpice();		
		
		assertNotEquals(c1.getOrder(), c2.getOrder(), "Value for MakeCoffee is the same for some reason");
	}
	
}
