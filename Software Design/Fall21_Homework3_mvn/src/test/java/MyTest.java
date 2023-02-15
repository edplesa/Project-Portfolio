import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {

	static Coffee order;
	@BeforeEach
	void setup() {
		order = CoffeeFactory.getCoffee("lr");
	}
	
	@Test
	void test1() {
		assertEquals(order.makeCoffee(),3.50,0.0f,"Light Roast Returning wrong value.");
	}	
	@Test
	void test2() {
		order = new Sugar(order);
		assertEquals(order.makeCoffee(),4.0,0.0f,"Light Roast with sugar Returning wrong value.");
	}
	@Test
	void test3() {
		order = new Cream(order);
		assertEquals(order.makeCoffee(),4.0,0.0f,"Light Roast with cream Returning wrong value.");
	}
	@Test
	void test4() {
		order = new Sugar(new Cream(order));
		assertEquals(order.makeCoffee(),4.50,0.0f,"Light Roast with sugar and cream Returning wrong value.");
	}
	@Test
	void test5() {
		order = new ExtraShot(new Sugar(new Cream(order)));
		assertEquals(order.makeCoffee(),6.0,0.0f,"Light Roast with sugar, cream, and extrashot Returning wrong value.");
	}
	

}
