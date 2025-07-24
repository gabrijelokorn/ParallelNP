const algoDetail = {
    "partition": {
        "c": {
            "seq": "Zaporedni program",
            "sgl_stc": "En problem se rešuje hkrati z nastavitvijo 'schedule(static)'",
        },
        "go": {
            "seq": "Zaporedni program",
            "sgl_stc": "Rešuje se en partition problem naenkrat, pri čemer se podmnožice rešujejo vzporedno",
        },
        "julia": {
            "seq": "Zaporedni program",
            "sgl_stc": "Vsak partition problem se rešuje zaporedno, pri čemer se vsak problem rešuje vzporedno (z nastavitvijo static)",
        },
    },
    "kamada_kawai": {
        "c": {
            "sgl_seq": "Premikamo en delec naenkrat, delte računamo sinhrono",
            "sgl_par": "Premikamo en delec naenkrat, delte računamo vzporedno",
            "mlt_seq": "Premikamo več delcev naenkrat, delte računamo sinhrono",
            "mlt_par": "Premikamo več delcev naenkrat, delte računamo vzporedno",
        },
        "go": {
            "sgl_seq": "Zaporedni program",
            "sgl_par": "Paralelni program",
        },
        "julia": {
            "sgl_seq": "Zaporedni program",
            "sgl_par": "Paralelni program",
        },
    },
}