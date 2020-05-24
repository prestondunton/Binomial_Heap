# Preston Dunton
# CS320 Honors Option
# May 20, 2020
# pdunton@rams.colostate.edu

# Extract_Min() Should be O(logn)

extract_min_binomial = read.csv("./extract_min_binomial.csv")
attach(extract_min_binomial)

summary(T)
# min 41
# q1 71
# median 84
# mean 96.5
# q3 107
# max 2553

plot(N,T,pch=18,xlab="N",ylab="Time (ns)",main="Binomial Heap.Extract_Min()")
hist(T,breaks=20)

# Let's see if we can remove some outliers

quantile(T,seq(0,1,0.1))
quantile(T,seq(0.9,1,0.01))

# Let's separate the top 1% and analyze

# Top 1%
  summary(T[which(T>247)])
  # min 248
  # q1 269
  # median 306
  # mean 401.7
  # q3 441
  # max 2553
  hist(T[which(T>247)],main="Histogram of Top 1% of Times",xlab="Time (ns)",breaks=20)
  
# Bottom 99%
  summary(T[which(T<=247)])
  # min 41
  # q1 71
  # median 84
  # mean 93.45
  # q3 106
  # max 247
  hist(T[which(T<=247)],main="Histogram of Bottom 99% of Times",xlab="Time (ns)",breaks=30)

detach(extract_min_binomial)