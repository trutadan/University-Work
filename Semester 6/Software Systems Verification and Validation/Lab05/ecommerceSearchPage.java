package org.example.pages;

import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.support.FindBy;

@DefaultUrl("https://ecommerce-playground.lambdatest.io/")
public class ecommerceSearchPage extends PageObject {

    @FindBy(xpath = "//*[@id=\"search\"]/div[1]/div[1]/div[2]/input")
    private WebElementFacade searchInput;

    @FindBy(xpath = "//*[@id=\"entry_212470\"]/div/div[2]")
    private WebElementFacade resultsDiv;

    @FindBy(xpath = "//*[@id=\"entry_212469\"]/p")
    private WebElementFacade noResultsDiv;

    public void enter_search_keyword_and_submit(String keyword) {
        searchInput.typeAndEnter(keyword);
    }

    public String get_valid_search_results_present() {
        return resultsDiv.getText();
    }

    public String get_invalid_search_message() {
        return noResultsDiv.getText();
    }
}
