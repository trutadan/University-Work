package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import net.thucydides.core.steps.ScenarioSteps;
import org.example.pages.ecommerceSearchPage;
import org.junit.Assert;

public class ecommerceSearchSteps extends ScenarioSteps {

    private ecommerceSearchPage page;

    @Step
    public void is_on_home_page() {
        page.open();
    }

    @Step
    public void performs_search(String keyword) {
        page.enter_search_keyword_and_submit(keyword);
    }

    @Step
    public void should_see_valid_search_results(String expectedMessage) {
        Assert.assertTrue("Valid search results were expected but not found.",
                page.get_valid_search_results_present().contains(expectedMessage));
    }

    @Step
    public void should_see_invalid_search_message(String expectedMessage) {
        Assert.assertEquals("Invalid search message did not match.",
                expectedMessage, page.get_invalid_search_message());
    }
}
