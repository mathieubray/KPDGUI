setwd("C:/Users/braym/Box Sync/Academic Work/KPD Project/KPDGUI/KPDGUI/solutions")

library(tidyverse)

exchanges_4 <- read_csv("KPDGUI_Tue_Aug_28_2018_13_38_23/ExchangeList.csv")

exchanges_5 <- read_csv("KPDGUI_Tue_Aug_28_2018_13_43_36/ExchangeList.csv")

exchanges_4_rel <- exchanges_4 %>% select(NodeIDs, AssignedValue, Nodes)
exchanges_5_rel <- exchanges_5 %>% select(NodeIDs, AssignedValue, Nodes) %>% rename(AssignedValue5 = AssignedValue)

merged <- left_join(exchanges_5_rel,exchanges_4_rel,by=c("NodeIDs","Nodes")) %>%
  filter(Nodes < 5) %>%
  mutate(SameAssignedVal = AssignedValue == AssignedValue5)

sum(merged$SameAssignedVal) == nrow(merged)
