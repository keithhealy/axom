-- Basic example of a simulation Input File
thermal_solver={}
thermal_solver.mesh = {
 filename = "/data/star.mesh",
 serial = 1,
 parallel = 1
}
thermal_solver.order = 2
thermal_solver.timestepper = "quasistatic"
-- define initial conditions
thermal_solver.u0 = { type = "function", func = "BoundaryTemperature"}
-- define conducitivity
thermal_solver.kappa = { type = "constant", constant = 0.5}
-- linear solver parameters
thermal_solver.solver = {
 rel_tol = 1.e-6,
 abs_tol = 1.e-12,
 print_level = 0,
 max_iter = 100,
 dt = 1.0,
 steps = 1 
}
-- boundary conditions
thermal_solver.bcs = {
  [1] = {
    attrs = { [1] = 3, [2] = 4, [3] = 7},
    constant = 12.2
  },
  [4] = {
    attrs = { [7] = 4, [12] = 6, [9] = 1},
    constant = -23.1
  }
}
