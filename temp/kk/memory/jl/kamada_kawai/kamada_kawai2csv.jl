module Kamada_Kawai2csv

using ..Kamada_Kawai

export writeState
function writeState(fp::IOStream, state::Vector{Coord})
    for i in 1:length(state)
        write(fp, string(state[i].x))
        write(fp, ",")
        write(fp, string(state[i].y))
        write(fp, "\n")
    end
    write(fp, "\n")
end # writeState

end # module