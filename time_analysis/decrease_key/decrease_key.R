# Preston Dunton
# CS320 Honors Option
# May 23, 2020
# pdunton@rams.colostate.edu

# Minimum() in a binomial heap should be O(logn)

decrease_key_binomial = read.csv("./decrease_key_binomial.csv")
attach(decrease_key_binomial)

summary(T)
# min 14
# q1 15
# median 19
# mean 19.75
# q3 21
# max 1152
plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial_Heap.Decrease_Key()")
hist(T,breaks=30)


# Let's see if we can remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))
quantile(T,seq(0.99,1,0.001))
quantile(T,seq(0.999,1,0.0001))

# Let's separate the top 0.01% and analyze

# Top 0.01%
sum(T>76) # There are 10 outliers
summary(T[which(T>76)])
# min 91
# q1 118.2
# median 135
# mean 419.5
# q3 826.8
# max 1152
hist(T[which(T>76)],main="Histogram of Top 0.01% of Times",xlab="Time (ns)",breaks=30)

# Bottom 99.99%
summary(T[which(T<=76)])
# min 14
# q1 15
# median 19
# mean 19.71
# q3 21
# max 76
hist(T[which(T<=76)],main="Histogram of Bottom 99.99% of Times",xlab="Time (ns)",breaks=30)

# 99.99% of deletions take less than 76 ns
# There also appears to be no large corelation between N and insertion time
# The implementation must be correct for an O(logn) time

detach(decrease_key_binomial)