from django.contrib import admin
from api.models import NutritionFactsPerScoop, ProteinPowder, MonohydrateCreatinePowder

# Register your models here.
admin.site.register(NutritionFactsPerScoop)
admin.site.register(ProteinPowder)
admin.site.register(MonohydrateCreatinePowder)