# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# Minimum() in a binomial heap should be O(logn)

minimum_binomial = read.csv("./minimum_binomial.csv")
attach(minimum_binomial)

summary(T)
# min 15
# q1 25
# median 28
# mean 29.01
# q3 33
# max 1331
plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial_Heap.Minimum()")
hist(T,breaks=20)

# Let's try to remove the outliers.  Most times fall below 100 ns

sum(T>100) # there are 3 outliers.
T[which(T>100)] # the are 1289, 1331, and 1246

# Let's remove the outliers and try again

  summary(T[which(T<100)])
  # min 15
  # q1 25
  # median 28
  # mean 28.97
  # q3 33
  # max 76
  plot(N[which(T<100)],T[which(T<100)],pch=18,xlab="N",ylab="Time (ns)",main="Binomial_Heap.Minimum() Excluding Outliers")
  # Better, but not a very useful representation of the data
  
  hist(T[which(T<100)],main="Histogram of Time Excluding Outliers",xlab="Time (ns)",breaks=30)

# Looks like most calls to minimum() take under 100 ns.
# There also doesn't appear to be a large correlation between T and N
# The implementation must be correct for an O(logn) time.

detach(minimum_binomial)