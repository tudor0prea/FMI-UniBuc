# Laborator 4

operatie_noua<- function (i,j) {
k=sqrt( abs(i-j) + 1)
return (1/k) }
M=outer(x1,x2, operatie_noua)
print(M)

x <- seq(0, 1, 0.1); 
plot(x, x - x * x + 2) plot(x, x - x * x + 2, type = "l");
plot(x, x - x * x + 2, type = "b", pch = 19)


?ChickWeight

