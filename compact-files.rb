require 'rails'

class RepositoryNames
  # Construção da classe
  def initialize(dir)
    @dir = dir
  end

  # Execução da classe
  def call
    remove_empty(@dir)
    normalize(@dir)
  end

  private

  # Remove pastas vazias
  def remove_empty(dir)
    Dir.glob(File.join(dir, '*')).each do |path|
      next unless File.directory?(path)

      remove_empty(path)
      Dir.rmdir(path) if Dir.empty?(path)
    end
  end

  # Normaliza arquivos e pastas
  def normalize(dir)
    Dir.glob(File.join(dir, '*')).each do |path|
      next rename_file(path) if File.file?(path)

      rename_folder(path)
      normalize(path)
    end
  end

  # Renomeia arquivos
  def rename_file(path)
    File.rename(path, "#{File.dirname(path)}/#{file_name(path)}#{file_extension(path)}")
  end

  # Renomeia pastas
  def rename_folder(path)
    File.rename(path, "#{File.dirname(path)}/#{folder_name(path)}")
  end

  # Estrutura nome do arquivo
  def file_name(path)
    name = File.basename(path, '.*')

    name.parameterize.gsub('_', '-')
  end

  # Estrutura nome da pasta
  def folder_name(path)
    name = File.basename(path)

    name.parameterize.gsub('_', '-')
  end

  # Estrutura extenção do arquivo
  def file_extension(path)
    File.extname(path)
  end
end

RepositoryNames.new(Dir.pwd).call
