module Kamada_Kawai2csv

using ..Kamada_Kawai

export writeVertices
function writeVertices(vertices::Vector{Vector{Coord}}, resultFile::String)
    file = open(resultFile, "w")

    for i in 1:length(vertices)
        for j in 1:length(vertices[i])
            write(file, string(vertices[i][j].x))
            write(file, ",")
            write(file, string(vertices[i][j].y))
            write(file, "\n")
        end
        write(file, "\n")
    end

    close(file)
end # writeVertices

end # module