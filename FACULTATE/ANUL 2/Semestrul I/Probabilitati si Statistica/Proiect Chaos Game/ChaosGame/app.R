library(shiny)
library(shape)

## Generators
# Triangle

tri.gen <- function(ratio){
  
  maxi <- 60000
  
  puncteInitiale <- matrix(ncol=3,nrow=3)
  
  puncteInitiale[1,] <- c(1,0,0)
  puncteInitiale[2,] <- c(2,0.5,0.85)
  puncteInitiale[3,] <- c(3,1,0)
  
  repartitieVarfuri <- runif(maxi)
  repartitieVarfuri[which(repartitieVarfuri>2/3)]<- 3
  repartitieVarfuri[which(1/3<repartitieVarfuri & repartitieVarfuri<=2/3)]<- 2
  repartitieVarfuri[which(repartitieVarfuri<=1/3)]<- 1
  
  puncte <- matrix(NA,ncol=2,nrow=(maxi+1))
  
  colnames(puncte)<-c("x","y")
  
  puncte[1,] <- c(runif(1),runif(1))
  
  for (i in 1:maxi){
    
    varf <- which(puncteInitiale[,1]==repartitieVarfuri[i])
    
    x <- puncteInitiale[varf,2]
    y <- puncteInitiale[varf,3]
    
    x.new <- ratio*x + (1-ratio)*puncte[i,1]
    y.new <- ratio*y + (1-ratio)*puncte[i,2]
    
    puncte[i+1,]<-c(x.new,y.new)
  }
  return(list(puncteInitiale,puncte))
}

# Square

sqr.gen <- function(ratio){
  
  maxi <- 60000
  
  puncteInitiale <- matrix(NA,ncol=3,nrow=4)
  
  puncteInitiale[1,] <- c(1,0.0,0.0)
  puncteInitiale[2,] <- c(2,1.0,0.0)
  puncteInitiale[3,] <- c(3,1.0,1.0)
  puncteInitiale[4,] <- c(4,0.0,1.0)
  
  repartitieVarfuri <- runif(maxi)
  repartitieVarfuri[which(repartitieVarfuri>3/4)]<- 4
  repartitieVarfuri[which(2/4<repartitieVarfuri & repartitieVarfuri<=3/4)]<- 3
  repartitieVarfuri[which(1/4<repartitieVarfuri & repartitieVarfuri<=2/4)]<- 2
  repartitieVarfuri[which(repartitieVarfuri<=1/4)]<- 1
  
  puncte <- matrix(NA,ncol=2,nrow=(maxi+1))
  colnames(puncte)<-c("x","y")
  
  puncte[1,] <- c(runif(1),runif(1))
  
  varfAnterior <- 0
  
  for (i in 1:maxi){
    while(repartitieVarfuri[i]==varfAnterior)
    {
      repartitieVarfuri[i] <- sample(1:4, 1)
    }
    varf <- which(puncteInitiale[,1]==repartitieVarfuri[i])
    varfAnterior <- repartitieVarfuri[i]
    x <- puncteInitiale[varf,2]
    y <- puncteInitiale[varf,3]
    x.new <- (ratio)*x + (1-ratio)*puncte[i,1]
    y.new <- (ratio)*y + (1-ratio)*puncte[i,2]
    puncte[i+1,]<-c(x.new,y.new)
  }
  
  return(list(puncteInitiale,puncte))
}


# Hexagon

hex.gen <- function(ratio){
  
  maxi <- 60000
  
  puncteInitiale <- matrix(NA,ncol=3,nrow=6)
  
  puncteInitiale[1,] <- c(1,0,1)
  puncteInitiale[2,] <- c(2, sqrt(3)/2, 0.5)
  puncteInitiale[3,] <- c(3, sqrt(3)/2, -0.5)
  puncteInitiale[4,] <- c(4,0, -1)
  puncteInitiale[5,] <- c(5, -sqrt(3)/2, -0.5)
  puncteInitiale[6,] <- c(6, -sqrt(3)/2, 0.5)
  
  repartitieVarfuri <- runif(maxi)
  repartitieVarfuri[which(repartitieVarfuri>5/6)]<- 6
  repartitieVarfuri[which(4/6<repartitieVarfuri & repartitieVarfuri<=5/6)]<- 5
  repartitieVarfuri[which(3/6<repartitieVarfuri & repartitieVarfuri<=4/6)]<- 4
  repartitieVarfuri[which(2/6<repartitieVarfuri & repartitieVarfuri<=3/6)]<- 3
  repartitieVarfuri[which(1/6<repartitieVarfuri & repartitieVarfuri<=2/6)]<- 2
  repartitieVarfuri[which(repartitieVarfuri<=1/6)]<- 1
  
  puncte <- matrix(NA,ncol=2,nrow=(maxi+1))
  
  colnames(puncte)<-c("x","y") 
  
  puncte[1,] <- c(runif(1, -sqrt(3)/2, sqrt(3)/2),runif(1,-1, 1))
  
  for (i in 1:maxi){
    
    varf <- which(puncteInitiale[,1]==repartitieVarfuri[i])
    
    x <- puncteInitiale[varf,2]
    y <- puncteInitiale[varf,3]
    
    x.new <- (ratio)*x + (1-ratio)*puncte[i,1]
    y.new <- (ratio)*y + (1-ratio)*puncte[i,2]
    
    puncte[i+1,]<-c(x.new,y.new)
  }
  
  return(list(puncteInitiale,puncte))
}

# Pentagon

ptg.gen <- function(ratio){
  
  maxi <- 60000
  
  puncteInitiale <- matrix(NA,ncol=3,nrow=5)
  
  r <- sqrt(50 + 10 * sqrt(5)) / 10
  
  puncteInitiale[1,] <- c(1, 0.0 , r) #a
  puncteInitiale[2,] <- c(2, sqrt(1-1/(4*r*r)), r - 1/(2*r)) #b
  puncteInitiale[3,] <- c(3, 1/2, (-1)* sqrt(r*r - 1/4)) #c
  puncteInitiale[4,] <- c(4, -1/2,(-1) * sqrt(r*r - 1/4)) #d 
  puncteInitiale[5,] <- c(5, -sqrt(1-1/(4*r*r)), r - 1/(2*r)) #e
  
  repartitieVarfuri <- runif(maxi)
  repartitieVarfuri[which(repartitieVarfuri>4/5)]<- 5
  repartitieVarfuri[which(3/5<repartitieVarfuri & repartitieVarfuri<=4/5)]<- 4
  repartitieVarfuri[which(2/5<repartitieVarfuri & repartitieVarfuri<=3/5)]<- 3
  repartitieVarfuri[which(1/5<repartitieVarfuri & repartitieVarfuri<=2/5)]<- 2
  repartitieVarfuri[which(repartitieVarfuri<=1/5)]<- 1
  
  puncte <- matrix(NA,ncol=2,nrow=(maxi+1))
  colnames(puncte)<-c("x","y")
  
  puncte[1,] <- c(runif(1),runif(1))
  
  varfAnterior <- 0
  
  for (i in 1:maxi){
    while(repartitieVarfuri[i]==varfAnterior)
    {
      repartitieVarfuri[i] <- sample(1:4, 1)
    }
    varf <- which(puncteInitiale[,1]==repartitieVarfuri[i])
    varfAnterior <- repartitieVarfuri[i]
    x <- puncteInitiale[varf,2]
    y <- puncteInitiale[varf,3]
    x.new <- (ratio)*x + (1-ratio)*puncte[i,1]
    y.new <- (ratio)*y + (1-ratio)*puncte[i,2]
    puncte[i+1,]<-c(x.new,y.new)
  }
  
  return(list(puncteInitiale,puncte))
}

# Barnsley Fern

fern.gen <- function(){
  
  maxi <- 60000
  
  const <- matrix(NA,ncol=7,nrow=4)
  
  const[1,] <- c(1, 0.0, 0.0, 0.0, 0.0, 0.16, 0.0)
  const[2,] <- c(2, 0.85, 0.04, 0.0, -0.04, 0.85, 1.6)
  const[3,] <- c(3, 0.2, -0.26, 0.0, 0.23, 0.22, 1.6)
  const[4,] <- c(4, -0.15, 0.28, 0.0, 0.26, 0.24, 0.44 )
  
  func <- runif(maxi)
  func[which(func>93/100)]<- 4
  func[which(86/100<func & func<=93/100)]<- 3
  func[which(1/100<func & func<=86/100)]<- 2
  func[which(func<=1/100)]<- 1
  
  puncte <- matrix(NA,ncol=2,nrow=(maxi+1))
  
  colnames(puncte)<-c("x","y") 
  
  puncte[1,] <- c(0,0)
  
  for (i in 1:maxi){
    id <- which(const[,1]==func[i])
    x <- puncte[i,1]
    y <- puncte[i,2]
    x.new <- const[id,2] * x + const[id,3] * y + const[id,4]
    y.new <- const[id,5] * x + const[id,6] * y + const[id,7]
    puncte[i+1,]<-c(x.new,y.new)
  }
  
  const <- matrix(NA,ncol=3,nrow=1)
  const[1,] <- c(1, 0.0, 0.0)
  
  return(list(const,puncte))
}


## Server


shinyServer(function(input, output, session) {
  
  
  all.list <- reactive({
    if(input$randomize){
      if (input$shape == "tri") {
        return(tri.gen(input$dist.tri))
      }
      if (input$shape == "sqr") {
        return(sqr.gen(input$dist.sqr))
      }
      if (input$shape == "hex") {
        return(hex.gen(input$dist.hex))
      }
      if (input$shape == "fern") {
        return(fern.gen())
      }
      if (input$shape == "ptg") {
        return(ptg.gen(input$dist.ptg))
      }
    }
    else {
      if (input$shape == "tri") {
        return(tri.gen(input$dist.tri))
      }
      if (input$shape == "sqr") {
        return(sqr.gen(input$dist.sqr))
      }
      if (input$shape == "hex") {
        return(hex.gen(input$dist.hex))
      }
      if (input$shape == "fern") {
        return(fern.gen())
      }
      if (input$shape == "ptg") {
        return(ptg.gen(input$dist.ptg))
      }
    }
    
  })
  
  # renderplot
  output$plot <- renderPlot({
    
    varfuri <- all.list()[[1]]
    puncte    <- all.list()[[2]]
    it <- input$slider
    
    # plot limits
    if(input$shape == "fern"){
      plot(0,0,xlim = c(-3, 3), ylim = c(0, 10))
    }
    else if(input$shape == "hex"){
      plot(0,0,xlim=c(-1,1),ylim=c(-1,1))
    }
    else if(input$shape == "ptg"){
      plot(0,0,xlim=c(-1,1),ylim=c(-1,1))
    }
    else{
      plot(0,0,xlim=c(0,1),ylim=c(0,1))
    }
    
    # afisare puncte
    if (it==1) {
      points(puncte[1,1],puncte[1,2],pch=20,cex=3,col="blue")  
      text(puncte[1,1],puncte[1,2]+0.05,"Random Starting Point",col="blue")
      
    }
    else if (it<=100) {
      points(puncte[1:it,1],puncte[1:it,2],pch=20,cex=1,col="blue")  
      points(puncte[it,1],puncte[it,2],pch=20,cex=2.75,col="blue")  
    }
    else if (it<200) {
      points(puncte[1:((it-100)*100+100),1],puncte[1:((it-100)*100+100),2],pch=".",cex=3,col="blue") 
    }
    else if (it<=249) {
      val <- (it-199)*1000+10000
      points(puncte[1:val,1],puncte[1:val,2],pch=".",cex=2.5,col="blue")
    }
    
    # puncte initiale
    points(varfuri[,2],varfuri[,3],pch=20,cex=2,col="red")
  }) 
})

