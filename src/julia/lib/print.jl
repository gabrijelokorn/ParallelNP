module Print

using JSON
using ..Kamada_Kawai

export fOutJsonArray, fOutStates

function fOutJsonArray(file, arr::Vector{Bool})
    jsonString = JSON.json(arr)
    write(file, jsonString)
end

function fOutStates(file, states::Vector{Vector{Coord}})
    for i in 1:length(states)
        for j in 1:length(states[i])
            println("states[i][j].x: ", states[i][j].x, " states[i][j].y: ", states[i][j].y)
            write(file, string(states[i][j].x))
            write(file, ",")
            write(file, string(states[i][j].y))
            write(file, "\n")
        end
        println("\n")
        write(file, "\n")
    end

end # fOutStates

end # module