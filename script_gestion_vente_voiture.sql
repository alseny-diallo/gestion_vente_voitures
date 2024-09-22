SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

-- Base de données : `gestionVenteVoiture`
CREATE DATABASE IF NOT EXISTS `gestionVenteVoiture` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `gestionVenteVoiture`;

SET FOREIGN_KEY_CHECKS = 0;


DROP TABLE IF EXISTS `ligneCommandes`;
DROP TABLE IF EXISTS `factures`;
DROP TABLE IF EXISTS `commandes`;
DROP TABLE IF EXISTS `voitures`;
DROP TABLE IF EXISTS `clients`;


SET FOREIGN_KEY_CHECKS = 1;


CREATE TABLE `clients` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(200) NOT NULL,
  `prenom` varchar(200) NOT NULL,
  `email` varchar(200) NOT NULL,
  `adresse` varchar(200) NOT NULL,
  `tel` bigint(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `voitures` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `marque` varchar(200) NOT NULL,
  `model` varchar(200) NOT NULL,
  `annee` int(11) NOT NULL,
  `kilométrage` varchar(200) NOT NULL,
  `prix` double NOT NULL,
  `description` varchar(200) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `commandes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `clientId` int(11) NOT NULL,
  `dateCommande` varchar(200) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`clientId`) REFERENCES `clients`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `factures` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `commandeId` int(11) NOT NULL,
  `dateFacture` varchar(200) NOT NULL,
  `montantTotal` double NOT NULL,
  `modePaiement` varchar(200) NOT NULL,
  `statut` varchar(200) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`commandeId`) REFERENCES `commandes`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `ligneCommandes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `commandeId` int(11) NOT NULL,
  `voitureId` int(11) NOT NULL,
  `quantite` int(11) NOT NULL,
  `prixUnitaire` double NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`commandeId`) REFERENCES `commandes`(`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (`voitureId`) REFERENCES `voitures`(`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


COMMIT;


INSERT INTO `clients` (`nom`, `prenom`, `email`, `adresse`, `tel`) VALUES
('Diop', 'Aissatou', 'aissatou.diop@example.com', '123 Rue de la République', 771234567),
('Sarr', 'Moussa', 'moussa.sarr@example.com', '45 Avenue de l\'Indépendance', 778765432),
('Fall', 'Fatou', 'fatou.fall@example.com', '67 Boulevard du 22 Mars', 776543210),
('Ngom', 'Cheikh', 'cheikh.ngom@example.com', '89 Rue de l\'Unité', 774321987),
('Ba', 'Mariama', 'mariama.ba@example.com', '11 Avenue du Général de Gaulle', 775432198),
('Thiam', 'Lamine', 'lamine.thiam@example.com', '22 Boulevard de la Liberté', 772345678),
('Kouyaté', 'Ndeye', 'ndeye.kouyate@example.com', '33 Rue des Martyrs', 779876543),
('Sow', 'Ibrahima', 'ibrahima.sow@example.com', '44 Avenue de la Paix', 778123456),
('Diallo', 'Oumy', 'oumy.diallo@example.com', '55 Rue de la Culture', 771234890),
('Toure', 'Souleymane', 'souleymane.toure@example.com', '66 Boulevard des Nations', 775678901);


INSERT INTO `voitures` (`marque`, `model`, `annee`, `kilométrage`, `prix`, `description`) VALUES
('Toyota', 'Corolla', 2020, '15000 km', 15000, 'Voiture en très bon état, peu utilisée'),
('Honda', 'Civic', 2019, '20000 km', 17000, 'Voiture en bon état, toutes options'),
('Ford', 'Fiesta', 2018, '25000 km', 13000, 'Voiture fiable et économique'),
('BMW', 'Serie 3', 2021, '10000 km', 35000, 'Berline de luxe, peu de kilomètres'),
('Mercedes', 'Classe A', 2022, '5000 km', 40000, 'Voiture de luxe, état neuf'),
('Peugeot', '208', 2020, '18000 km', 14000, 'Voiture compacte, bien entretenue'),
('Renault', 'Clio', 2019, '22000 km', 12000, 'Petite voiture économique et pratique'),
('Audi', 'A4', 2021, '12000 km', 32000, 'Voiture haut de gamme, comme neuve'),
('Volkswagen', 'Golf', 2018, '30000 km', 16000, 'Voiture sportive, très bon état'),
('Nissan', 'Qashqai', 2020, '15000 km', 28000, 'SUV spacieux, très confortable');


INSERT INTO `commandes` (`clientId`, `dateCommande`) VALUES
(1, '2024-09-20'),
(2, '2024-09-21'),
(3, '2024-09-22');


INSERT INTO `factures` (`commandeId`, `dateFacture`, `montantTotal`, `modePaiement`, `statut`) VALUES
(1, '2024-09-21', 16000, 'Carte bancaire', 'Payée'),
(2, '2024-09-22', 17000, 'Virement bancaire', 'En attente'),
(3, '2024-09-23', 13000, 'Espèces', 'Payée');


INSERT INTO `ligneCommandes` (`commandeId`, `voitureId`, `quantite`, `prixUnitaire`) VALUES
(1, 1, 1, 15000),
(2, 2, 1, 17000),
(3, 3, 1, 13000);

