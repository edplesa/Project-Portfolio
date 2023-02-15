import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class SavingsMethodTest {
	
	static MyMoney s1;
	
	@BeforeAll
	static void setup() {
		s1 = new MyMoney("values.txt", "values2.txt",8,8);
	}
	
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
		assertEquals(32110,Math.round(SavingsFormulas.futureValueLS_VariableInterest(20000, s1.getInterestValues())), "wrong value futureLumpSumVariableInterest");
	}
	@Test
	void testFutureValueLS_VariableInterest2() {
		assertEquals(0,Math.round(SavingsFormulas.futureValueLS_VariableInterest(0, s1.getInterestValues())), "wrong value futureLumpSumVariableInterest2");
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
		assertEquals(130788,Math.round(SavingsFormulas.compoundSavingsVariable(s1.getCashValues(), .09)), "wrong value for testCompoundSavingsVariable");
	}
	@Test
	void testCompoundSavingsVariable2() {
		assertEquals(98500,Math.round(SavingsFormulas.compoundSavingsVariable(s1.getCashValues(), 0)), "wrong value for testCompoundSavingsVariable2");
	}
	
	
	
	
}
