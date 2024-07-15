package org.example.features.search;

import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.steps.serenity.ecommerceSearchSteps;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/ecommerceSearchTestData.csv")
public class ecommerceSearchTests {

    @Managed
    public WebDriver webdriver;

    @Steps
    public ecommerceSearchSteps user;

    private String searchQuery;
    private String resultType;
    private String expectedText;

    @Test
    public void testSearchFunctionality() throws InterruptedException {
        user.is_on_home_page();
        Thread.sleep(2000);

        user.performs_search(searchQuery);
        Thread.sleep(2000);

        if ("valid".equals(resultType)) {
            user.should_see_valid_search_results(expectedText);
        } else if ("invalid".equals(resultType)) {
            user.should_see_invalid_search_message(expectedText);
        }
    }
}
