# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# Should be O(1). Empty() asks if the heap is empty and returns a boolean, unlike
# clear(), which removes all elements from the heap

empty_binomial = read.csv("C:/Users/Preston/Desktop/CS320/HonOpt/empty_binomial.csv")
attach(empty_binomial)

summary(T)
# min 13
# q1 14
# median 15
# mean 14.64
# q3 15
# max 1520

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial Heap.Empty()")
hist(T,breaks=20)

# Let's try and remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))
quantile(T,seq(0.99,1,0.001))
quantile(T,seq(0.999,1,0.0001))
quantile(T,seq(0.9999,1,0.00001))

# Let's separate and anylze the top 0.005%

# Top 0.005%
sum(T>108) # There are 5 outliers
summary(T[which(T>108)])
# min 122
# q1 237
# median 248
# mean 691.4
# q3 1330
# max 1520
hist(T[which(T>108)],main="Histogram of Top 0.005% of Times",xlab="Time (ns)",breaks=20)

# Bottom 99.995%
summary(T[which(T<=108)])
# min 13
# q1 14
# median 15
# mean 14.61
# q3 15
# max 108
hist(T[which(T<=108)],main="Histogram of Bottom 99.995% of Times",xlab="Time (ns)",breaks=20)

# Let's get a better histogram to look at.
# Bottom 99.993%
hist(T[which(T<=25)],breaks=20)

# With some outliers (possible context switches or longer memory accesses)
# the time is on average 14.64.  Obviously O(1)

detach(empty_binomial)