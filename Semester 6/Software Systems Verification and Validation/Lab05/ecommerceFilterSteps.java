package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import net.thucydides.core.steps.ScenarioSteps;
import org.example.pages.ecommerceFilterPage;
import org.junit.Assert;

public class ecommerceFilterSteps extends ScenarioSteps {
    private ecommerceFilterPage page;

    @Step
    public void is_on_home_page() {
        page.open();
    }

    @Step
    public void performs_filter(String lowerPrice, String higherPrice) {
        page.select_price_filters(lowerPrice, higherPrice);
    }

    @Step
    public void should_see_valid_search_results(String expectedMessage) {
        Assert.assertTrue("Valid filtering results were found.",
                page.get_valid_search_results().contains(expectedMessage));
    }

    @Step
    public void should_see_empty_search_results(String expectedMessage) {
        Assert.assertEquals("No filtering results were found.",
                expectedMessage, page.get_invalid_search_results());
    }
}
