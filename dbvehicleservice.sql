-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 20, 2022 at 07:38 AM
-- Server version: 10.4.22-MariaDB
-- PHP Version: 8.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbvehicleservice`
--

-- --------------------------------------------------------

--
-- Table structure for table `roadtax`
--

CREATE TABLE `roadtax` (
  `RegistrationNo` varchar(10) COLLATE utf8mb4_bin NOT NULL,
  `RoadTaxID` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `EffectiveDate` date NOT NULL,
  `ExpiryDate` date NOT NULL,
  `PolicyNo` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `StartDate` date NOT NULL,
  `EndDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `roadtax`
--

INSERT INTO `roadtax` (`RegistrationNo`, `RoadTaxID`, `EffectiveDate`, `ExpiryDate`, `PolicyNo`, `StartDate`, `EndDate`) VALUES
('CXZ1234', '1234-A', '2022-01-13', '2023-01-13', 'A-0000', '2022-01-13', '2023-01-13'),
('BNM7890', 'A-1222', '2020-01-15', '2021-01-15', '9090120', '2020-01-15', '2021-01-15'),
('BNP6788', 'M-121209', '2020-01-01', '2021-01-01', 'MMM1234', '2020-01-01', '2021-01-01'),
('BNP6788', 'X-10982', '2022-01-20', '2023-01-20', '120911A', '2022-01-20', '2023-01-20'),
('VKM1677', 'X-109823', '2019-01-20', '2020-01-20', '120911ZA', '2019-01-20', '2020-01-20'),
('TBX6677', 'Z-10998', '2021-01-01', '2022-01-01', '0909123', '2021-01-01', '2022-01-01');

-- --------------------------------------------------------

--
-- Table structure for table `service`
--

CREATE TABLE `service` (
  `RegistrationNo` varchar(10) COLLATE utf8mb4_bin NOT NULL,
  `ReceiptNo` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `Date` date NOT NULL,
  `Cost` double NOT NULL,
  `ServiceMileage` double NOT NULL,
  `NextMileage` double NOT NULL,
  `DateMileage` date NOT NULL,
  `ServiceType` varchar(20) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `service`
--

INSERT INTO `service` (`RegistrationNo`, `ReceiptNo`, `Date`, `Cost`, `ServiceMileage`, `NextMileage`, `DateMileage`, `ServiceType`) VALUES
('BNP6788', 'A-01', '2022-01-01', 120, 10000, 15000, '2022-01-31', 'Minor'),
('CXZ1234', 'A-1234', '2022-01-13', 200, 10000, 15000, '2022-02-13', 'Minor'),
('BNM7890', 'AAA1234', '2022-01-10', 100, 10000, 15000, '2022-02-01', 'Minor'),
('BNM7890', 'ABC123', '2021-12-01', 100, 10000, 20000, '2022-01-14', 'Minor'),
('TBX6677', 'ABC1234', '2022-01-01', 90, 9000, 15000, '2022-01-31', 'Minor'),
('BNP6788', 'B-01', '2022-01-31', 130, 15000, 20000, '2022-02-22', 'Minor'),
('BNM7890', 'X-123', '2022-02-01', 130.1, 20000, 30000, '2022-02-28', 'Minor');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `UserID` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `Password` varchar(50) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`UserID`, `Password`) VALUES
('ahmad', 'abc123'),
('sitiaishah', 'abc123');

-- --------------------------------------------------------

--
-- Table structure for table `vehicle`
--

CREATE TABLE `vehicle` (
  `RegistrationNo` varchar(10) COLLATE utf8mb4_bin NOT NULL,
  `VehicleType` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `VehicleModel` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `VehicleColour` varchar(20) COLLATE utf8mb4_bin NOT NULL,
  `VehicleStatus` enum('Registered','Deactivate','','') COLLATE utf8mb4_bin NOT NULL DEFAULT 'Registered',
  `UserID` varchar(50) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `vehicle`
--

INSERT INTO `vehicle` (`RegistrationNo`, `VehicleType`, `VehicleModel`, `VehicleColour`, `VehicleStatus`, `UserID`) VALUES
('BNM7890', 'SUV', 'Proton', 'Blue', 'Registered', 'sitiaishah'),
('BNP6788', 'Hatchback', 'Honda', 'Blue', 'Registered', 'sitiaishah'),
('CAB1234', 'Hatchback', 'Perodua', 'Black', 'Deactivate', 'sitiaishah'),
('CXZ1234', 'Van', 'Toyota', 'White', 'Registered', 'sitiaishah'),
('KKK7788', 'Sedan', 'Toyota', 'Red', 'Registered', 'ahmad'),
('PFQ9999', 'Pickup', 'Honda', 'White', 'Registered', 'ahmad'),
('TBX6677', 'Sedan', 'Perodua', 'Black', 'Registered', 'sitiaishah'),
('VKM1677', 'Van', 'Proton', 'White', 'Deactivate', 'sitiaishah'),
('XVR1234', 'SUV', 'Proton', 'Blue', 'Deactivate', 'sitiaishah');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `roadtax`
--
ALTER TABLE `roadtax`
  ADD PRIMARY KEY (`RoadTaxID`),
  ADD KEY `RegistrationNo` (`RegistrationNo`);

--
-- Indexes for table `service`
--
ALTER TABLE `service`
  ADD PRIMARY KEY (`ReceiptNo`),
  ADD KEY `service_ibfk_1` (`RegistrationNo`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`UserID`);

--
-- Indexes for table `vehicle`
--
ALTER TABLE `vehicle`
  ADD PRIMARY KEY (`RegistrationNo`),
  ADD KEY `UserID` (`UserID`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `roadtax`
--
ALTER TABLE `roadtax`
  ADD CONSTRAINT `roadtax_ibfk_1` FOREIGN KEY (`RegistrationNo`) REFERENCES `vehicle` (`RegistrationNo`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `service`
--
ALTER TABLE `service`
  ADD CONSTRAINT `service_ibfk_1` FOREIGN KEY (`RegistrationNo`) REFERENCES `vehicle` (`RegistrationNo`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `vehicle`
--
ALTER TABLE `vehicle`
  ADD CONSTRAINT `vehicle_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `user` (`UserID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
