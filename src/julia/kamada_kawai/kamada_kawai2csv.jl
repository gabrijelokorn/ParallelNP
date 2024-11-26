module Kamada_Kawai2csv

using ..Kamada_Kawai

export WriteVertices
function WriteVertices(file, states::Vector{Vector{Coord}})
    for i in 1:length(states)
        for j in 1:length(states[i])
            write(file, string(states[i][j].x))
            write(file, ",")
            write(file, string(states[i][j].y))
            write(file, "\n")
        end
        write(file, "\n")
    end

end # WriteVertices

end # module