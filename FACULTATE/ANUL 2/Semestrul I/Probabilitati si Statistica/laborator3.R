data()
mtcars()
aggregate( wt ~ am,
          FUN=mean,
          data=mtcars)

aggregate(  wt ~ cyl,
           FUN=mean,
           data=mtcars)

aggregate( mpg ~ cyl+am,
           FUN=mean,
           data=mtcars)
#fara formula= merge
aggregate(formula = weight ~ Diet, # DV este weight, IV este Diet
          FUN = mean, # calculeaza media pentru fiecare grup
          data = ChickWeight)