module Write

using Printf

export writeTime
function writeTime(file, time)
    time_str = @sprintf("%.9f", time)  # 9 decimal p
    write(file, string(time_str))
end # writeTime
end # module

