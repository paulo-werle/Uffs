import matplotlib.pyplot as plt
from tabulate import tabulate
import numpy as np
import math

class Bisection:
  ##### Entradas #####
  def __init__(self):
    self.inA     = -0.1
    self.inB     = 0
    self.epsilon = 1e-06
    self.outputs = []

    self.xMin = self.inA
    self.xMax = self.inB

  def function(self, x):
    # return -2 * pow(x, 3) + 5 * pow(x, 2) + x - 6
    return -0.5 * pow(x, 2) - 4 * math.sin(2 * x)

  ##### Processamento #####
  def method(self):
    return (self.inA + self.inB) / 2

  def comparation(self):
    return (self.inB - self.inA) <= self.epsilon

  def includeOutput(self, iteration, value):
    self.outputs.append([ iteration, self.inA, self.inB, value, self.function(value) ])

  def bisection(self):
    if self.comparation(): return
    value = self.function(self.inA)
    iterations = 0

    while True:
      x = self.method()
      if value * self.function(x) > 0:
        self.inA = x
      else:
        self.inB = x

      self.includeOutput(iterations, x)
      iterations += 1
      if self.comparation(): return

  ##### Saida #####
  def printValues(self):
    print(tabulate(self.outputs, headers=['Iteração', 'A', 'B', 'X', 'f(x)']))

  def generateGraph(self):
    linspace = np.linspace(self.xMin, self.xMax, 100)

    plt.figure(dpi = 100, figsize = (5, 5))
    plt.suptitle("Metodo da Bisseção")
    plt.hlines(y = 0, xmin = self.xMin, xmax = self.xMax)
    plt.plot(linspace, self.function(linspace), color = 'blue')
    for output in self.outputs:
      plt.plot(output[3], 0, marker = 'o', color= 'red')
    plt.show()

##### Execução #####
instance = Bisection()
instance.bisection()
instance.printValues()
# instance.generateGraph()
print(instance.inA, instance.inB)
