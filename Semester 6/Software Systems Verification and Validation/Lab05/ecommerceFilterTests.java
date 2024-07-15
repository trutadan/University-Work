package org.example.features.search;

import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.steps.serenity.ecommerceFilterSteps;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/ecommerceFilterTestData.csv")
public class ecommerceFilterTests {

    @Managed
    public WebDriver webdriver;

    @Steps
    public ecommerceFilterSteps user;

    private String lowerPrice;
    private String higherPrice;
    private String resultType;
    private String expectedText;

    @Test
    public void testFilterFunctionality() throws InterruptedException {
        user.is_on_home_page();
        Thread.sleep(2000);

        user.performs_filter(lowerPrice, higherPrice);
        Thread.sleep(2000);

        if ("valid".equals(resultType)) {
            user.should_see_valid_search_results(expectedText);
        } else if ("invalid".equals(resultType)) {
            user.should_see_empty_search_results(expectedText);
        }
    }
}
