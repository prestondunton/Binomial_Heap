# Preston Dunton
# CS320 Honors Option
# May 23, 2020
# pdunton@rams.colostate.edu

# Delete_Node() in a binomial heap should be O(logn)

delete_node_binomial = read.csv("./delete_node_binomial.csv")
attach(delete_node_binomial)

summary(T)
# min 44
# q1 69
# median 83
# mean 88.43
# q3 103
# max 1518
plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial_Heap.Delete_Node()")
hist(T,breaks=30)


# Let's see if we can remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))
quantile(T,seq(0.99,1,0.001))

# Let's separate the top 0.1% and analyze

# Top 0.1%
sum(T>227) # There are 100 outliers
summary(T[which(T>227)])
# min 228
# q1 243
# median 276.5
# mean 497.1
# q3 492
# max 1518
hist(T[which(T>227)],main="Histogram of Top 0.1% of Times",xlab="Time (ns)",breaks=30)

# Bottom 99.9%
summary(T[which(T<=227)])
# min 44
# q1 69
# median 83
# mean 88.02
# q3 103
# max 227
hist(T[which(T<=227)],main="Histogram of Bottom 99.9% of Times",xlab="Time (ns)",breaks=30)

# 99.9% of deletions take less than 227 ns
# There also appears to be no large corelation between N and insertion time
# The implementation must be correct for an O(logn) time

detach(delete_node_binomial)