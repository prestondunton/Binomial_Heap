# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# the copy constructor should be hould be O(n)
# where n is the size of the array to be copied

copy_binomial = read.csv("./copy_ctor_binomial.csv")
attach(copy_binomial)

summary(T)
# min 727
# q1 498590
# median 1020990
# mean 1060626
# q3 1612424
# max 2881307

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Copy Constructor for Binomial Heap")
hist(T,breaks=30)

# Let's see if we can remove some outliers

sum(T>2500000) # There's only one point that seems to lie above the rest. 
# this will not strongly affect our analysis

# Let's see if we can correlate N and T.  It appears to be a linear relationship, as we expect.

cor(N,T) # very strong corelation of 0.9972907

model = lm(T~N)
summary(model)

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Copy Constructor for Binomial Heap")
abline(model,lwd=2,col="red")

# The data seen for the copy constructor is clearly linear, which is expected given that
# to copy a heap, you must copy each element.
# Our linear regersion model tells us that for each additional element in the heap, 
# copying takes about 22.7604 extra nanoseconds.
# Complexity is O(n)

detach(copy_binomial)