from django.db import models

class Unit(models.Model):
    # some sort of correspondence to boost units si
    # currently very primitive method of identification
    suffix = models.CharField(max_length=20)

# V flexible on dependent / independent parameters atm
# Good thing?
class Metric(models.Model):
    unit = models.ForeignKey(Unit)
    name = models.CharField(max_length=40)


class Record(models.Model):
    value = models.FloatField()
    metric = models.ForeignKey(Metric)
    
class Experiment(models.Model):
    parameters = models.ManyToManyField(Metric,related_name='parameter_value_set')
    results = models.ManyToManyField(Metric,related_name='result_value_set')

class Run(models.Model):
    start_time = models.DateTimeField()
    end_time = models.DateTimeField()
    #Could Record extra clock cycles type info?
    experiment = models.ForeignKey(Experiment)
    
    parameters = models.ManyToManyField(Record,related_name='parameter_metric_set')
    results = models.ManyToManyField(Record,related_name='result_metric_set')