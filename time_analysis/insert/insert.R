# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# insert() Should be O(logn)

insert_binomial = read.csv("./insert_binomial.csv")
attach(insert_binomial)

summary(T)
# min 45
# q1 59
# median 65
# mean 74.4
# q3 70.0
# max 3219

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial_Heap.Insert()")
hist(T,breaks=20)

# Let's see if we can remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))
quantile(T,seq(0.98,0.99,0.001))

# Let's separate the top 1.5% and analyze

# Top 1.5%
sum(T>100) # There are 1498 outliers
summary(T[which(T>100)])
# min 101
# q1 661
# median 679
# mean 738.2
# q3 712
# max 3219
hist(T[which(T>100)],main="Histogram of Top 1.5% of Times",xlab="Time (ns)",breaks=20)

# Bottom 98.5%
summary(T[which(T<=100)])
# min 45
# q1 59
# median 65
# mean 64.61
# q3 69
# max 100
hist(T[which(T<=100)],main="Histogram of Bottom 98.5% of Times",xlab="Time (ns)",breaks=20)

# 98.5% of insertions take less than 100 ns
# There also appears to be no large corelation between N and insertion time
# The implementation must be correct for an O(logn) time

detach(insert_binomial)