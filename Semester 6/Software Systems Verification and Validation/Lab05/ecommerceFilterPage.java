package org.example.pages;

import net.serenitybdd.core.pages.PageObject;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.support.FindBy;

@DefaultUrl("https://ecommerce-playground.lambdatest.io/")
public class ecommerceFilterPage extends PageObject {

    @FindBy(xpath = "//*[@id=\"search\"]/div[2]/button")
    private WebElementFacade searchButton;

    @FindBy(xpath = "//*[@id=\"mz-filter-panel-0-0\"]/div/div[2]/input[1]")
    private WebElementFacade lowerPriceSlide;

    @FindBy(xpath = "//*[@id=\"mz-filter-panel-0-0\"]/div/div[2]/input[2]")
    private WebElementFacade higherPriceSlide;

    @FindBy(xpath = "//*[@id=\"entry_212469\"]/p")
    private WebElementFacade noResultsDiv;

    @FindBy(xpath = "//*[@id=\"entry_212470\"]/div/div[2]")
    private WebElementFacade resultsDiv;

    public void select_price_filters(String lowerPrice, String higherPrice) {
        searchButton.click();
        lowerPriceSlide.type(lowerPrice);
        higherPriceSlide.typeAndEnter(higherPrice);
    }

    public String get_valid_search_results() {
        return resultsDiv.getText();
    }

    public String get_invalid_search_results() {
        return noResultsDiv.getText();
    }
}
