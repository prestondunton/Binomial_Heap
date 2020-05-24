# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# size() can be implemented in an O(1) and an O(logn) way.
# To do it in O(1) time, keep a size_ member in the Binomial_Heap object
# and update it for insertions / deletions.  In this case, size() just returns that field.
# To do it in O(logn) time, iterate through the linked list of binomial trees
# and use the degree of the head of each tree to calculate how many nodes are in each tree.
# Because the length of that list is at most logn, size() is O(logn).
# I implemented the O(logn) way because I didn't feel like writing the O(1) implementation.

size_binomial = read.csv("./size_binomial.csv")
attach(size_binomial)

summary(T)
# min 45
# q1 140
# median 157
# mean 160
# q3 181
# max 17085

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial Heap.Size()")
hist(T,breaks=20)

# Let's see if we can remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))

# Let's separate the top 1% and analyze

# Top 1%
  sum(T>232) # There are 986 outliers
  summary(T[which(T>232)])
  # min 233
  # q1 234
  # median 236
  # mean 307.4
  # q3 246
  # max 17085
  hist(T[which(T>232)],main="Histogram of Top 1% of Times",xlab="Time (ns)",breaks=30)

# Bottom 99%
  summary(T[which(T<=232)])
  # min 45
  # q1 140
  # median 156
  # mean 159.1
  # q3 181
  # max 232
  hist(T[which(T<=232)],main="Histogram of Bottom 99% of Times",xlab="Time (ns)",breaks=30)

  
  # Looks like most calls to size() take under 232 ns.
  # There also doesn't appear to be a large correlation between T and N
  # The implementation appears to be O(logn) time like the other operations that have this trend.
  # An O(1) implementation could be achieved by implementing a size_ member, but I don't want to
  # bother with that.

detach(size_binomial)