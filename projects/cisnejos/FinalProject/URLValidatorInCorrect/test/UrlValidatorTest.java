

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {	
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.google.com/"));
	   System.out.println(urlVal.isValid("256.256.256.256"));
	   System.out.println(urlVal.isValid("http://138.197.198.178:-1"));;
	   System.out.println(urlVal.isValid("http://www.google.com/test1"));
   }
   
   
   public void testYourFirstPartition() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\ntest Url Scheme");
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   System.out.println(urlVal.isValid("3ht://www.google.com"));
   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\ntest Url Authority");
	   System.out.println(urlVal.isValid("http://www.go.com"));
	   System.out.println(urlVal.isValid("256.256.256.256"));
   }

   public void testYourThirdPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\ntest Url Port");
	   System.out.println(urlVal.isValid("http://138.197.198.178:65535"));
	   System.out.println(urlVal.isValid("http://138.197.198.178:-1"));
   }
   
   public void testYourFourthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\ntest Path");
	   System.out.println(urlVal.isValid("http://www.google.com/test1"));
	   System.out.println(urlVal.isValid("http://www.google.com/../"));
   }
   
   public void testYourFifthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\ntest Url Query");
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action=view"));
   }
   
 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
