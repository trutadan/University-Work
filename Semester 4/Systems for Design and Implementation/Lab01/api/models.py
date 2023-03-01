from django.db import models

# Create your models here.
class NutritionFactsPerScoop(models.Model):
    size_in_grams = models.PositiveSmallIntegerField()
    calories = models.PositiveSmallIntegerField()
    fat = models.PositiveSmallIntegerField()
    carbohydrate = models.PositiveSmallIntegerField()
    protein = models.PositiveSmallIntegerField()

    def __str__(self):
        return f'a scoop of {self.size_in_grams}g contains: {self.calories} calories, {self.fat}g fats, {self.carbohydrate}g carbohydrates, {self.protein}g protein'


class ProteinPowder(models.Model):
    protein_name = models.CharField(max_length=30)
    producer_name = models.CharField(max_length=50)
    flavour = models.CharField(max_length=20)
    quantity_in_grams = models.PositiveSmallIntegerField()
    scoop_nutrition_facts = models.ForeignKey(NutritionFactsPerScoop, default=None, blank=True, null=True, on_delete=models.SET_NULL)
    is_vegan = models.BooleanField()

    def __str__(self):
        return f'{self.quantity_in_grams}g of {self.protein_name} protein by {self.producer_name}'
