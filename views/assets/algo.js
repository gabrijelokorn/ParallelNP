const algoDetail = {
    "partition": {
        "c": {
            "seq": "Zaporedni program",
            "mlt_stc": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "mlt_dyn": "Več problemov se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_dyn": "En problem se rešuje hkrati z nastavitvijo 'schedule(dynamic)'",
            "sgl_stc": "En problem se rešuje hkrati z nastavitvijo 'schedule(static)'",
            "nested": "Gnezdeni paralelizem - več problemov se izvaja vzporedno 'schedule(dynamic)', pri čemer se tudi vsak posamičen problem izvaja vzporedno 'schedule(static)'",
        },
        "go": {
            "seq": "Zaporedni program",
            "mlt_all_chn": "Vsak partition problem je dinamično dodeljen svoji goroutine-i. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_dyn_chn": "Dinamično porazdeljevanje dela med goroutine - z uporabo kanalov. Goroutine-i so sinhronizirani z uporabo kanalov",
            "mlt_all": "Vsak partition problem je dinamično dodeljen svoji goroutine-i.",
            "sgl_dyn": "Rešuje se en partition problem naenkrat, pri čemer se podmnožice rešujejo vzporedno (sinhronizirane s kanali)",
            "nested": "Vsakemu partition problemu pripada ena goroutina, ki ga kasneje rešuje hkrati več goroutin"
        },
        "julia": {
            "seq": "Zaporedni program",
            "mlt_stc": "Več partition problemov se rešuje vzporedno (statična porazdelitev med threade), pri čemer se vsak problem rešuje zaporedno",
            "mlt_dyn": "Več partition problemov se rešuje vzporedno (dinamična porazdelitev med threade), pri čemer se vsak problem rešuje zaporedno",
            "sgl_dyn": "Vsak partition problem se rešuje zaporedno, pri čemer se vsak problem rešuje vzporedno (z nastavitvijo static)",
            "sgl_dyn": "Vsak partition problem se rešuje zaporedno, pri čemer se vsak problem rešuje vzporedno (z nastavitvijo dynamic)"
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