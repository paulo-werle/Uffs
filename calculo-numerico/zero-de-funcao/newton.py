import matplotlib.pyplot as plt
from tabulate import tabulate
import numpy as np
import math

class Newton:
  ##### Entradas #####
  def __init__(self):
    self.inX     = -0.5
    self.epsilon = 1e-06
    self.outputs = []

    self.xMin = -self.inX
    self.xMax = self.inX

  def inX():
    return float(self.inX)

  def function(self, x):
    # return -2 * pow(x, 3) + 5 * pow(x, 2) + x - 6
    return -0.5 * pow(x, 2) - 4 * math.sin(2 * x)

  def derivativeFunction(self, x):
    # return -6 * pow(x, 2) + 10 * x + 1
    return - x - 8 * math.cos(2 * x)

  ##### Processamento #####
  def method(self):
    return self.inX - (self.function(self.inX) / self.derivativeFunction(self.inX))

  def comparation(self):
    return abs(self.function(self.inX)) <= self.epsilon

  def includeOutput(self, iteration):
    self.outputs.append([ iteration, self.inX, self.function(self.inX), self.derivativeFunction(self.inX) ])

  def newton(self):
    if self.comparation(): return
    iterations = 0

    while True:
      self.inX = self.method()

      self.includeOutput(iterations)
      iterations += 1
      if self.comparation(): return

  ##### Saida #####
  def printValues(self):
    print(tabulate(self.outputs, headers=['Iteração', 'X', 'f(x)', 'df(x)']))

  def generateGraph(self):
    linspace = np.linspace(self.xMin, self.xMax, 100)

    plt.figure(dpi = 100, figsize = (5, 5))
    plt.suptitle("Metodo de Newton")
    plt.hlines(y = 0, xmin = self.xMin, xmax = self.xMax)
    plt.plot(linspace, self.function(linspace), color = 'blue')
    for output in self.outputs:
      plt.plot(output[1], 0, marker = 'o', color= 'red')
    plt.show()

##### Execução #####
instance = Newton()
instance.newton()
instance.printValues()
# instance.generateGraph()
print(instance.inX)
