import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class SavingsMethodTest {
	
	static MyMoney s1;
	static MyMoney s2;
	
	@BeforeAll
	static void setup() {
		s1 = new MyMoney("values.txt", 8);
		s2 = new MyMoney("values2.txt", 8);
	}
	
	/*@Test
	void savingsTest() {
	
		//use dollar amounts from the file at a constant rate of 7%
		assertEquals(65388,Math.round(SavingsFormulas.compoundSavingsVariable(s1.getValues(), .07)), "wrong value");
	}*/
	
	@Test
	void constantSavingsTest() {
		
		//save $20,000 yearly at 7% for 10 years
		assertEquals(276329,Math.round(SavingsFormulas.compoundSavingsConstant(20000, .07, 10)), "wrong value");
	}
	
	@Test
	void constantSavingsTwoTest() {
		
		//save $1000 yearly at 5% for 5 years
		assertEquals(5526,Math.round(SavingsFormulas.compoundSavingsConstant(1000, .05, 5)), "wrong value");
	}
	
	@Test
	void futureValLumpSumTest() {
		
		//future value of $20,000 over 10 years at 7%
		assertEquals(39343,Math.round(SavingsFormulas.futureValueLumpSum(20000, .07, 10)), "wrong value");
	}
	
	@Test
	void futureValLumpSumTwoTest() {
		
		//future value of $10,000 over 5 years at 5%
		assertEquals(12763,Math.round(SavingsFormulas.futureValueLumpSum(10000, .05, 5)), "wrong value");
	}
	
	/*@Test
	void fvVariableRateTest() {
		
		//future value of $20,000 at variable rates per year from the file
		assertEquals(29166,Math.round(SavingsFormulas.futureValueLS_VariableInterest(20000, s2.getValues())), "wrong value");
	}*/
	
	@Test
	void testFutureValueLumpSum() {
		assertEquals(39343, Math.round(SavingsFormulas.futureValueLumpSum(20000, .07, 10)), "Wrong Value for futurelumpsum");
	}	
	@Test
	void testFutureValueLumpSum2() {
		assertEquals(0, Math.round(SavingsFormulas.futureValueLumpSum(0, .07, 10)), "Wrong Value for futurelumpsum2");
	}
	
	
	
	@Test
	void testFutureValueLS_VariableInterest() {
		assertEquals(32110,Math.round(SavingsFormulas.futureValueLS_VariableInterest(20000, s2.getValues())), "wrong value futureLumpSumVariableInterest");
	}
	@Test
	void testFutureValueLS_VariableInterest2() {
		assertEquals(0,Math.round(SavingsFormulas.futureValueLS_VariableInterest(0, s2.getValues())), "wrong value futureLumpSumVariableInterest2");
	}
	
	
	
	
	@Test
	void testCompoundSavingsConstant() {
		assertEquals(276329,Math.round(SavingsFormulas.compoundSavingsConstant(20000, .07, 10)), "wrong value for compundSavingsConstant");
	}
	@Test
	void testCompoundSavingsConstant2() {
		assertEquals(0,Math.round(SavingsFormulas.compoundSavingsConstant(0, .07, 10)), "wrong value for compundSavingsConstant2");
	}
	
	
	
	
	
	@Test
	void testCompoundSavingsVariable() {
		assertEquals(130788,Math.round(SavingsFormulas.compoundSavingsVariable(s1.getValues(), .09)), "wrong value for testCompoundSavingsVariable");
	}
	@Test
	void testCompoundSavingsVariable2() {
		assertEquals(98500,Math.round(SavingsFormulas.compoundSavingsVariable(s1.getValues(), 0)), "wrong value for testCompoundSavingsVariable2");
	}
}
