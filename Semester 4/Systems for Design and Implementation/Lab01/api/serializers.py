from rest_framework import serializers
from api.models import NutritionFactsPerScoop, ProteinPowder

class NutritionFactsPerScoopSerializer(serializers.ModelSerializer):
    class Meta:
        model = NutritionFactsPerScoop
        fields = ('__all__')

class ProteinPowderSerializer(serializers.ModelSerializer):
    class Meta:
        model = ProteinPowder
        fields = ('__all__')