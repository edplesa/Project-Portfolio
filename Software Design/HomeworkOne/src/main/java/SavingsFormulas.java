
public class SavingsFormulas {

	/*private double helper_futureValueLS_VariableInterest(double cash, double values[], int length) {
		if (length <= 0) 
			return 0;
		return (helper_helper_futureValueLS_VariableInterest(cash, values, length));
	}*/
	
	public static double futureValueLumpSum(double cash, double interest, int years) {
		return cash * Math.pow((1 + interest), years);
	}
	
	public static double futureValueLS_VariableInterest(double cash, double values[]) {
		for (int i = 0; i < values.length; i++ ) {
			cash = cash * (1 + values[i]);
		}
		return cash;
	}
	
	public static double compoundSavingsConstant(double cash, double interest, int years) {
		return cash * ((Math.pow((1 + interest), years) - 1) / interest);
	}
	
	public static double compoundSavingsVariable(double values[], double interest) {
		double year = values[0];
		for (int i = 1; i < values.length; i++) {
			year = (year * (1 + interest)) + values[i];
		}
		return year;
	}
	
	
}
