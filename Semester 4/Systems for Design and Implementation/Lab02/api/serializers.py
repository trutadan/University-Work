from rest_framework import serializers
from api.models import NutritionFactsPerScoop, ProteinPowder, MonohydrateCreatinePowder

class NutritionFactsPerScoopSerializer(serializers.ModelSerializer):
    class Meta:
        model = NutritionFactsPerScoop
        fields = ('__all__')

class NutritionFactsPerScoopListSerializer(serializers.ModelSerializer):
    class Meta:
        model = NutritionFactsPerScoop
        fields = ('id',)


class ProteinPowderSerializer(serializers.ModelSerializer):
    class Meta:
        model = ProteinPowder
        fields = ('__all__')

class ProteinPowderListSerializer(serializers.ModelSerializer):
    class Meta:
        model = ProteinPowder
        fields = ('id',)


class MonohydrateCreatinePowderSerializer(serializers.ModelSerializer):
    class Meta:
        model = MonohydrateCreatinePowder
        fields = ('__all__')

class MonohydrateCreatinePowderListSerializer(serializers.ModelSerializer):
    class Meta:
        model = MonohydrateCreatinePowder
        fields = ('id',)