#By izanbf1803
elevators = []
blocked = False
obj = None              # Definition of global variables to use each one along the code.
last_floor = 0
new_floor = False


# nb_floors: number of floors
# width: width of the area
# nb_rounds: maximum number of rounds
# exit_floor: floor on which the exit is found
# exit_pos: position of the exit on its floor
# nb_total_clones: number of generated clones
# nb_additional_elevators: ignore (always zero)
# nb_elevators: number of elevators
nb_floors, width, nb_rounds, exit_floor, exit_pos, nb_total_clones, nb_additional_elevators, nb_elevators = [int(i) for i in input().split()]
for i in range(nb_elevators):
    # elevator_floor: floor on which this elevator is found
    # elevator_pos: position of the elevator on its floor
    elevator_floor, elevator_pos = [int(j) for j in input().split()]
    elevators.append({
        "floor": elevator_floor,
        "pos": elevator_pos,
    })

while True:
    # clone_floor: floor of the leading clone
    # clone_pos: position of the leading clone on its floor
    # direction: direction of the leading clone: LEFT or RIGHT
    clone_floor, clone_pos, direction = input().split()
    floor = int(clone_floor)
    pos = int(clone_pos)
    
    if last_floor < floor: #If it's on a new floor, set <new_floor> True
        new_floor = True
    
    closest_elevator = None
    reachable_elevators = [i for i in elevators if i["floor"] == floor]
    _closest = 999999
    
    if len(reachable_elevators) > 0:
        for i in reachable_elevators:           # This bucle it's getting the closest elevator
            if abs(pos - i["pos"]) < _closest:  
                _closest = abs(pos - i["pos"])
                closest_elevator = i        
        obj = closest_elevator                  # Set the closest elevator as "objective"
    else:
        obj = {                                 # If no elevators found in the floor, set the exit as "objective"
            "floor": exit_floor, 
            "pos": exit_pos,
        }
        
        
    if direction == "LEFT":
        if obj["pos"] > pos and not blocked:    # If direction it's "LEFT" and objective it's to the right,
            print("BLOCK")                      #   block the leading clone to change direction.
            blocked = True
        else:
            print("WAIT")
    else:
        if obj["pos"] < pos and not blocked:    # If direction it's "RIGHT" and objective it's to the left,
            print("BLOCK")                      #   block the leading clone to change direction.
            blocked = True  
        else:
            print("WAIT")
    
    

    if new_floor:             # If the leading clone it's on a new floor, any clone is blocking, set <blocked> to False,
        blocked = False       #    and update las floor.
        last_floor = floor
        new_floor = False
