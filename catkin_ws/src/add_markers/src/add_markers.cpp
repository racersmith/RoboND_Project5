// subscribe to move_base/status
// status_list.status
// 1 == goal accepted, trying to reach goal
// 3 == goal reached
// This will tell us if we should pick up or put down the object

// subscribe to move_base/goal
// goal.target_pose.pose.position.x,y
// This will give us where to place the object