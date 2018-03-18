

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
	   assertEquals("http://www.google.com/ should validate", true, urlVal.isValid("http://www.google.com/"));
	   assertEquals("256.256.256.256 should not validate", false, urlVal.isValid("256.256.256.256"));
	   assertEquals("http://www.google.com/test1 should validate", true, urlVal.isValid("http://www.google.com/test1"));
	   assertEquals("http://138.197.198.178:-1 should not validate", false, urlVal.isValid("http://138.197.198.178:-1"));
   }
   
   
   public void testYourFirstPartition() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.google.com should validate", true, urlVal.isValid("http://www.google.com"));
	   assertEquals("3ht://www.google.com should not validate", false, urlVal.isValid("3ht://www.google.com"));
   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.go.coms should  validate", true, urlVal.isValid("http://www.go.com"));
	   assertEquals("256.256.256.256 should not validate", false, urlVal.isValid("256.256.256.256"));
   }

   public void testYourThirdPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://138.197.198.178:65535 should validate", true, urlVal.isValid("http://138.197.198.178:65535"));
	   assertEquals("http://138.197.198.178:-1 should not validate", false, urlVal.isValid("http://138.197.198.178:-1"));
   }
   
   public void testYourFourthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.google.com/test1 should validate", true, urlVal.isValid("http://www.google.com/test1"));
	   assertEquals("http://www.google.com/../ should not validate", false, urlVal.isValid("http://www.google.com/../"));
   }
   
   public void testYourFifthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.amazon.com/?action=view should validate", true, urlVal.isValid("http://www.amazon.com/?action=view"));
   }
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
}
