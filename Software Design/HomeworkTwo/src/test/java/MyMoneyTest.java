import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyMoneyTest {
	
	private static int iter;
	private static double cashVals[] = new double[] {4000,5500,15000,18000,24000,9000,11000,12000}; 
	private static double interestVals[] = new double[] {.055,.075,.045,.09,.10,.065,.035,.025};
	
	@BeforeAll
	static void setup() {
		iter = 0;		
	}
	
	
	@ParameterizedTest
	@ValueSource(doubles = {4000,5500,15000,18000,24000,9000,11000,12000})
	void testMyMoneyWithOneCashFile(double arg) {
		MyMoney s1 = new MyMoney("values.txt",8,1);		
		assertEquals(s1.getCashValues()[iter],arg, "Cash Values array incorrect");
		iter++;
	}
	
	@Test
	void testMyMoneyInterestArrUninit() {
		MyMoney s1 = new MyMoney("values.txt",8,1);
		assertEquals(s1.getInterestValues(),null, "Interest Values were initialized for some reason");
	}
	
	@Test	
	void testMyMoneyWithOneInterestFile() {		
		MyMoney s1 = new MyMoney("values2.txt",8,2);		
		assertArrayEquals(s1.getInterestValues(),interestVals, "Interest Values array incorrect");		
	}
	
	@Test
	void testMyMoneyCashArrUninit() {
		MyMoney s1 = new MyMoney("values2.txt",8,2);
		assertEquals(s1.getCashValues(),null, "Cash Values were initialized for some reason");
	}
	
	@Test
	void testMyMoneyBothFilesConstructorForCash() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertArrayEquals(s1.getCashValues(), cashVals, "Second constructor cash values are incorrect");
	}
	
	@Test
	void testMyMoneyBothFilesConstructorForInterest() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertArrayEquals(s1.getInterestValues(), interestVals, "Second constructor interest values are incorrect");
	}
	
	@Test
	void testMyMoneyBothFilesConstructorForBoth() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertArrayEquals(s1.getCashValues(), cashVals, "Second constructor cash values are incorrect");
		assertArrayEquals(s1.getInterestValues(), interestVals, "Second constructor interest values are incorrect");
	}
	
	@Test
	void testMyMoneyLumpSumConstant() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(0, Math.round(s1.lumpSum_ConstantRate(0, 0.055, 4)), "MyMoney LumpSumConstant is incorrect");		
	}
	
	@Test
	void testMyMoneyLumpSumConstant2() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(38906, Math.round(s1.lumpSum_ConstantRate(15000, 0.1, 10)), "MyMoney LumpSumConstant2 is incorrect");		
	}
	
	@Test
	void testMyMoneyLumpSumVariable() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(0, Math.round(s1.lumpSum_VariableRate(0)), "MyMoney LumpSumVariable is incorrect");		
	}
	
	@Test
	void testMyMoneyLumpSumVariable2() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(6422, Math.round(s1.lumpSum_VariableRate(4000)), "MyMoney LumpSumVariable2 is incorrect");		
	}
	
	@Test
	void testMyMoneyCompoundSavingsConstant() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(0, Math.round(s1.compoundSavings_sameContribution(0, 0.055, 5)), "MyMoney CompoundSavingsConstant is incorrect");		
	}
	
	@Test
	void testMyMoneyCompoundSavingsConstant2() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(22324, Math.round(s1.compoundSavings_sameContribution(4000, 0.055, 5)), "MyMoney CompoundSavingsConstant2 is incorrect");		
	}
	
	@Test
	void testMyMoneyCompoundSavingsVariable() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(117110, Math.round(s1.compoundSavings_variableContribution(0.055)), "MyMoney CompoundSavingsVariable is incorrect");		
	}
	
	@Test
	void testMyMoneyCompoundSavingsVariable2() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertEquals(98500, Math.round(s1.compoundSavings_variableContribution(0)), "MyMoney CompoundSavingsVariable2 is incorrect");		
	}
	
	@Test
	void testMyMoneyGetCashValuesOneFile() {
		MyMoney s1 = new MyMoney("values.txt",8,1);
		assertArrayEquals(cashVals, s1.getCashValues(), "MyMoney getCashValuesOneFile is incorrect");		
	}
	
	@Test
	void testMyMoneyGetCashValuesBothFiles() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertArrayEquals(cashVals, s1.getCashValues(), "MyMoney getCashValuesBothFiles is incorrect");		
	}
	
	
	@Test
	void testMyMoneyGetInterestValuesBothFiles() {
		MyMoney s1 = new MyMoney("values.txt", "values2.txt",8,8);
		assertArrayEquals(interestVals, s1.getInterestValues(), "MyMoney getInterestValuesBothFiles is incorrect");		
	}
	
	@Test
	void testMyMoneyGetInterestValuesOneFile() {
		MyMoney s1 = new MyMoney("values2.txt",8,2);
		assertArrayEquals(interestVals, s1.getInterestValues(), "MyMoney getInterestValuesOneFile is incorrect");		
	}
}
