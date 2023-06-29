library(shiny)
library(shinyBS)
library(shape)


ui <- shinyUI(
  # creates a fluid page layout divided in rows, which in turn include columns
  fluidPage(
    tags$title("PS Project: Chaos Game"),
    tags$h3("PS Project: Chaos Game"),
    # a shiny layout, which partitions the layout of the page in a side panel and a main panel
    sidebarLayout(
      sidebarPanel (
        # an input from which the user can choose, in a drop down list form
        selectizeInput(
          # the inputId is relevant to be tracked down in the server
          inputId = 'shape',
          tags$h5(tags$b('Shape')),
          choices = list("Shapes" = c(
            `Triangle` = 'tri',
            `Pentagon` = 'pent'
          )),
          selected = 'tri'
        ),
        # Creates a panel that is visible or not, depending on the value of a JavaScript expression. The JS expression is evaluated once at startup and whenever Shiny detects a relevant change in input/output.
        conditionalPanel(
          condition = "input.shape=='tri'",
          # another input from which the user can choose, in a slider form
          # this input will determine the ration that the point will move from a veretice to another
          sliderInput(
            inputId = "dist.tri",
            label = h5(tags$b("Distance ratio:")),
            min = 0.01,
            max = .99,
            # the default ratio is .5 for the triangle, so it can form the Sierpinski triangle
            value = .50,
            step = .01
          ),
          div("Default ratio: 0.50",
              style = "font-size: 9.5pt;color:teal", align = "left")
        ),
        
        conditionalPanel(
          condition = "input.shape=='pent'",
          sliderInput(
            inputId = "dist.pent",
            label = h5(tags$b("Distance ratio:")),
            min = 0.01,
            max = .99,
            # same stuff, now for the Sierpinski pentagon, where the default ratio is ~.63
            value = .63,
            step = .01
          ),
          div("Default ratio: 0.63", style = "font-size: 9.5pt;color:teal", align =
                "left")
        ),
        br(),
        # Render a reactive output variable as HTML within an application page. The text will be included within an HTML div tag, and is presumed to contain HTML content which should not be escaped.
        div(uiOutput(outputId = "my.pts")),
        br(),
        # it creates a button named "Randomize"
        div(bsButton(inputId = "generate", label = "Randomize"), align = "right")
      ),
      # end of sidePanel
      mainPanel("Visualisation:", value = 3,
                fluidRow(
                  div(div(plotOutput("compPlot")),
                      align = "center"),
                  HTML(
                    "<hr style='height: 2px; color: #BDBDBD; background-color: #D9D9D9; border: none;'>"
                  )
                ))
    )
  ))
# end of UI

# ------------------------------------------------------------------------------------------------------------

# Triangle
tri.generate <- function(wt) {
  len <- 50000
  
  # loc_index matrix represends the endpoints
  loc_index <- matrix(NA, ncol = 3, nrow = 3)
  
  # the coords of the 3 points will be (0,0), (0.5,sqrt(3)/2) and (1,0), so they fit nicely in the canvas
  loc_index[1,] <- c(1, 0, 0)
  loc_index[2,] <- c(2, 0.5, sqrt(3) / 2)
  loc_index[3,] <- c(3, 1, 0)
  
  # vertexes represents all the points' "direction", they will either go to point 1, 2 or 3
  # runif(len) offers 50k numbers between 0 and 1
  vertexes <- runif(len)
  
  # the points/vertexes will either get the value 1, 2 or 3 depending on what third between 0 and 1 are they placed
  vertexes[which(vertexes > 2 / 3)] <- 3
  vertexes[which(1 / 3 < vertexes & vertexes <= 2 / 3)] <- 2
  vertexes[which(vertexes <= 1 / 3)] <- 1
  
  # we allocate a matrix to host all the coords of every point that will be generated
  coords <- matrix(NA, ncol = 2, nrow = (len + 1))
  colnames(coords) <- c("x", "y") # ggvis
  
  # the first generated point will have random generated coords, 0<x<1 and 0<y<sqrt(3)/2 (so it fits in the canvas)
  coords[1,] <- c(runif(1), runif(1) * sqrt(3) / 2)
  
  for (i in 1:len) {
    # spot is the spot where the new point will go to (to which endpoint)
    spot <- vertexes[i]
    # x and y will take the coordinates of the chosen endpoint
    x <- loc_index[spot, 2]
    y <- loc_index[spot, 3]
    # x.new and y.new will move towards the endpoint, starting from the last point's spot
    x.new <- wt * x + (1 - wt) * coords[i, 1]
    y.new <- wt * y + (1 - wt) * coords[i, 2]
    # the new coordinates are passed down to the next point
    coords[i + 1,] <- c(x.new, y.new)
    #x <- x.new
    #y <- y.new
  }
  # it will return the 3 endpoints, the vertexes' "directions" and the coords of the vertexes
  return(list(loc_index, vertexes, coords))
}

# Pentagon
pent.generate <- function(wt) {
  len <- 50000
  loc_index <- matrix(NA, ncol = 3, nrow = 5)
  
  # these will be the value of the coords of the endpoints
  c1 <- 0.25 * (sqrt(5) - 1)
  c2 <- 0.25 * (sqrt(5) + 1)
  s1 <- 0.25 * (sqrt(10 + 2 * sqrt(5)))
  s2 <- 0.25 * (sqrt(10 - 2 * sqrt(5)))
  
  loc_index[1,] <- c(1, 0, 1)
  loc_index[2,] <- c(2, s1, c1)
  loc_index[3,] <- c(3, s2,-c2)
  loc_index[4,] <- c(4,-s2,-c2)
  loc_index[5,] <- c(5,-s1, c1)
  
  vertexes <- runif(len)
  # same stuff as before, but now the points will randomly be given 1/2/3/4/5 as "direction" values
  vertexes[which(vertexes > 4 / 5)] <- 5
  vertexes[which(3 / 5 < vertexes & vertexes <= 4 / 5)] <- 4
  vertexes[which(2 / 5 < vertexes & vertexes <= 3 / 5)] <- 3
  vertexes[which(1 / 5 < vertexes & vertexes <= 2 / 5)] <- 2
  vertexes[which(vertexes <= 1 / 5)] <- 1
  
  coords <- matrix(NA, ncol = 2, nrow = (len + 1))
  colnames(coords) <- c("x", "y") # ggvis
  
  # random coordinates for the first point, again
  coords[1,] <- c(runif(1,-s1, s1), runif(1,-c2, 1))
  
  for (i in 1:len) {
    spot <- vertexes[i]
    x <- loc_index[spot, 2]
    y <- loc_index[spot, 3]
    x.new <- (wt) * x + (1 - wt) * coords[i, 1]
    y.new <- (wt) * y + (1 - wt) * coords[i, 2]
    coords[i + 1,] <- c(x.new, y.new)
  }
  return(list(loc_index, vertexes, coords))
}



# ------------------------------------------------------------------------------------------------------------

server <- shinyServer(function(input, output, session) {
  # in the place where we said that "it will exist a reactive <div> somewhere in the server, now we build it in here
  # we build it inside the server so that we can change the values in the server and so that it won't affect the whole application, only whatever is shared with it, in this case the generation of the points
  output$my.pts <- renderUI({
    input$shape
    sliderInput(
      "pts",
      "Number of points:",
      min = 1000,
      max = 50000,
      step = 1000,
      value = 1000,
      animate = animationOptions(interval = 200)
    )
  })
  
  # button from shinyBS that will help randomize 
  updateButton(
    session,
    inputId = "generate",
    style = "primary",
    size = "default",
    disabled = FALSE
  )
  
  # all.list is a reactive expression that will return the values either from tri.generate, or from pent.generate
  all.list <- reactive({
    if (input$shape == "tri") {
      #
      return(tri.generate(input$dist.tri * (input$generate > -1)))
    }
    if (input$shape == "pent") {
      return(pent.generate(input$dist.pent * (input$generate > -1)))
    }
  })
  
  # the renderPlot builds a responsive plot, the output will pass down what has been built to the server
  output$compPlot <- renderPlot({
    # we'll be able to work with the values from the functions inside a reactive plot, which means that any change will refresh the plot
    loc_index <- all.list()[[1]]
    # vertexes  <- all.list()[[2]]
    coords    <- all.list()[[3]]
    
    # Triunghi
    if (input$shape == "tri") {
      # mar represent the margin of the plot, a little space between all the other elements
      par(mar = c(0.5, 0.5, 0.5, 0.5))
      plot(
        0,
        0,
        # the limiting of the x and y max values, equivalent of limiting the canvas in our case
        xlim = c(0, 1),
        ylim = c(0, sqrt(3) / 2),
        # n stands for "no plotting", so they won't show the values on the x and y axes
        yaxt = "n",
        xaxt = "n",
        # no labels for the x & y axes
        xlab = "",
        ylab = ""
        # , bty = "n"
      )
    }
    
    # Pentagon
    if (input$shape == "pent") {
      c1 <- 0.25 * (sqrt(5) - 1)
      c2 <- 0.25 * (sqrt(5) + 1)
      s1 <- 0.25 * (sqrt(10 + 2 * sqrt(5)))
      s2 <- 0.25 * (sqrt(10 - 2 * sqrt(5)))
      
      (mar = c(0.5, 0.5, 0.5, 0.5))
      plot(
        0,
        0,
        xlim = c(-s1, s1),
        ylim = c(-c2, 1),
        col = 0,
        yaxt = "n",
        xaxt = "n",
        xlab = "",
        ylab = ""
        # , bty = "n"
      )
    }
    
    # stylizing the blue points, the generated ones
    points(
      coords[1:input$pts, 1],
      coords[1:input$pts, 2],
      pch = ".",
      cex = 2.5,
      col = "blue"
    )
    
    # stylizing the red points, the endpoints
    points(
      loc_index[, 2],
      loc_index[, 3],
      pch = 20,
      cex = 2,
      col = "red"
    )
  })
})

# shinyApp builds the whole responsive shiny app, which will take the 'ui' and 'server' values to work with
shinyApp(ui = ui, server = server)