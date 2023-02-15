import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {

	@Test
	void testAbstractFactoryJet() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Jet");
		assertNotNull(whichFactory, "Abstract Factory for jet was created null.");		
	}
	@Test
	void testAbstractFactoryBoat() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Boat");
		assertNotNull(whichFactory, "Abstract Factory for Boat was created null.");	
	}
	@Test
	void testAbstractFactoryTank() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Tank");
		assertNotNull(whichFactory, "Abstract Factory for tank was created null.");	
	}
	@Test
	void testAbstractFactoryWeirdInput() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("3232");
		assertNull(whichFactory, "Abstract Factory for tank was created for some reason.");	
	}
	@Test
	void testGetVehicleAbramsFromAbstractFactoryTank() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Tank");
		Vehicle v1 = whichFactory.getVehicle("Abrams");
		assertNotNull(v1, "Vehicle from abstract factory for tank was created null.");	
	}
	@Test
	void testGetVehicleSU50FromAbstractFactoryJet() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Jet");
		Vehicle v1 = whichFactory.getVehicle("SU50");
		assertNotNull(v1, "Vehicle from abstract factory for jet was created null.");	
	}
	@Test
	void testGetVehicleRCBFromAbstractFactoryBoat() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Boat");
		Vehicle v1 = whichFactory.getVehicle("RCB");
		assertNotNull(v1, "Vehicle from abstract factory for boat was created null.");	
	}	
	@Test
	void testGetVehicleFromAbstractFactoryBoatWithWeirdInput() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Boat");
		Vehicle v1 = whichFactory.getVehicle("");
		assertNull(v1, "Vehicle from abstract factory for boat is not null for some reason.");	
	}	
	@Test
	void testGetVehicleFromAbstractFactoryTankWithWeirdInput() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Tank");
		Vehicle v1 = whichFactory.getVehicle("");
		assertNull(v1, "Vehicle from abstract factory for tank is not null for some reason.");	
	}
	@Test
	void testGetVehicleFromAbstractFactoryJetWithWeirdInput() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Jet");
		Vehicle v1 = whichFactory.getVehicle("");
		assertNull(v1, "Vehicle from abstract factory for jet is not null for some reason.");	
	}
	
	@Test
	void testWhatTypeFromJetSu50() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Jet");
		Vehicle v1 = whichFactory.getVehicle("SU50");
		assertEquals(v1.whatType(), "SU50 created and ready for shipment!","String from whatType for jet(SU50) is incorrect.");	
	}
	@Test
	void testWhatTypeFromBoatDV15() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Boat");
		Vehicle v1 = whichFactory.getVehicle("DV15");
		assertEquals(v1.whatType(), "DV15 attack boat created and ready for shipment!","String from whatType for boat(DV15) is incorrect.");	
	}
	@Test
	void testWhatTypeFromTankT90() {
		AbstractFactory whichFactory = VehicleProducer.getFactory("Tank");
		Vehicle v1 = whichFactory.getVehicle("T90");
		assertEquals(v1.whatType(), "T90 tank created and ready for shipment!","String from whatType for tank(T90) is incorrect.");	
	}
	
	
}
